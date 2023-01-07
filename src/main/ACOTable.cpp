#include<cmath>
#include"Ant.hpp"
#include"ACOTable.hpp"

//引数にACOTableColumnを取るfindGetterという関数で、Antクラスの、引数がvoid、返値がdoubleな、フィールドを変えない関数(const)の関数ポインタを返す
static double (Ant::*findGetter(ACOTableColumn col))() const {
  switch (col){
    case ACOTableColumn::PHEROMONE:
      return &Ant::pheromone;
    case ACOTableColumn::COST:
      return &Ant::allCost;
  }
  __builtin_unreachable();
}

ACOTable::ACOTable(){
  //NOTE: 時間経過してもフェロモンの順序関係は変わらないのでこれで良い
  new (this) multiset([this](const Ant *a,const Ant *b){return a->pheromone()>b->pheromone();});
}

const Ant* ACOTable::dropout(){
  if(this->size()<=this->max_size)return nullptr;
  auto target=this->begin();
  const Ant* ret=*target;
  this->erase(target);
  return ret;
}

inline void ACOTable::setCapacity(ll size){this->max_size=size;}
inline ll ACOTable::getCapacity() const {return this->max_size;}

double ACOTable::sum(ACOTableColumn target) const {
  double (Ant::*getter)(void)const=findGetter(target);
  double ret=0;
  for(const Ant* a:*this)ret+=(a->*getter)();
  return ret;
}

inline double ACOTable::mean(ACOTableColumn target) const {
  return this->sum(target)/this->size();
}

double ACOTable::variance(ACOTableColumn target) const {
  double (Ant::*getter)(void)const=findGetter(target);
  double sum=0,square_sum=0,temp;
  for(const Ant *a:*this){
    temp=(a->*getter)();
    sum+=temp;square_sum+=temp*temp;
  }
  double mean=sum/this->size();
  return square_sum/this->size()-mean*mean;
}

inline double ACOTable::stdev(ACOTableColumn target) const {
  return sqrt(this->variance(target));
}
