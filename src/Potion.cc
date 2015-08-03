#include "Potion.hh"
#include "Character.hh"
#include "Game.hh"
#include "Floor.hh"
#include "collision_masks.hh"
#include "CollectComponent.hh"
#include "main.hh"

Potion::Potion(effect_type effect, int amount)
  : effect_(effect)
  , amount_(amount)
{}

static
void adjust(Character *p, effect_type effect, int amount)
{
  if (effect & EFFECT_NEGATIVE)
    amount = -amount;

#define ADJUST_STAT(UPCASE, DOWNCASE)           \
  if (p && (effect & EFFECT_ ## UPCASE))        \
    p->DOWNCASE(p->DOWNCASE() + amount);

  ADJUST_STAT(ATK, atk);
  ADJUST_STAT(DEF, def);
  ADJUST_STAT(HEALTH, health);
#if 0
  ADJUST_STAT(HEALTH, max_hp);
#endif

#undef ADJUST_STAT
}

Potion::Modifier::Modifier()
  : p_(NULL)
  , effect_(EFFECT_NONE)
  , amount_(0)
{}

Potion::Modifier::Modifier(Character &p, effect_type effect, int amount)
  : p_(&p)
  , effect_(effect)
  , amount_(amount)
{
  adjust(p_, effect_, amount_);
}

Potion::Modifier::~Modifier()
{
  adjust(p_, effect_, -amount_);
}

Potion::Modifier::Modifier(const Modifier &other)
  : p_(other.p_)
  , effect_(other.effect_)
  , amount_(other.amount_)
{
  adjust(p_, effect_, amount_);
}

Potion::Modifier &Potion::Modifier::operator=(Modifier other)
{
  using std::swap;
  swap(*this, other);
  return *this;
}

void Potion::apply(Character &p)
{
  amount_ += amount_ * p.potion_bonus();
  if (effect_ & EFFECT_EXTENDED)
    game.floor()->modifications.push_back(Potion::Modifier(p, effect_, amount_));
  else
    adjust(&p, effect_, amount_);
}

struct PotionCollection: CollectComponent {
  void collectMe(GameObject &me, GameObject &collector) {
    if (collector.stats)
      me.use_potion(*collector.stats);
  }
};

static shared_ptr<PotionCollection> po_collect =
  make_shared<PotionCollection>();

GameObjectPtr make_potion(effect_type effect, int amount)
{
  GameObjectPtr out = make_basic_object('P');
  switch (effect) {
#define D(EFF, NAME)                                            \
  case EFFECT_ ## EFF: out->name = NAME; break
    D(HEALTH, "Health Potion");
    D(DAMAGE, "Damage Poison");
    D(BUFF_ATK, "Strength Potion");
    D(BUFF_DEF, "Defence Potion");
    D(NERF_ATK, "Strength Poison");
    D(NERF_DEF, "Defence Poison");
#undef D
  default: out->name = "Unknown Potion"; break;
  }

  out->potion_use = make_shared<Potion>(effect, amount);
  out->collision_mask = COLL_DOOR;
  if (config["advanced_game"])
    out->collect = po_collect;
  else
    out->collision_mask |= COLL_PLAYER;
  return out;
}

