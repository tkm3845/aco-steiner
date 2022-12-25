#include"Ant.hpp"
#include"ACOTable.hpp"

ACOTable::ACOTable(){
  //NOTE: 時間経過してもフェロモンの順序関係は変わらないのでこれで良い
  multiset([this](Ant *a,Ant *b){return a->pheromone(time)>b->pheromone(time);});
}
double ACOTable::costVariance(){
  double sum=0,square_sum=0,temp;
  for(Ant *a:*this){
    temp=a->getAllCost();
    sum+=temp;square_sum+=temp*temp;
  }
  return (square_sum-sum)/this->size();
}
void ACOTable::insert(Ant *a){
  multiset::insert(a);
  if(this->size()>this->max_size)this->erase(this->begin());
}
void ACOTable::setTime(ll time){this->time=time;}
void ACOTable::setTableSize(ll size){this->max_size=size;}