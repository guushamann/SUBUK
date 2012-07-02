//TCollection.h
#include <vector>
using namespace std;
template <class TBase> 
class TCollection
{
protected:
  //The Vector container that will hold the collection of Items
  vector<TBase> m_items;
public:
  int Add(void) 
  {
    //Create a new base item
    TBase BaseItem; 
    //Add the item to the container
    m_items.push_back(BaseItem); 
    //Return the position of the item within the container. 
    //Zero Based
    return (m_items.size()-1); 
  }
  //Function to return the memory address of a specific Item
  TBase* GetAddress(int ItemKey) 
  {
    return &(m_items[ItemKey]);
  }
  //Remove a specific Item from the collection
  void Remove(int ItemKey) 
  {
    //Remove the Item using the vector’s erase function
    m_items.erase(GetAddress(ItemKey)); 
  }
  void Clear(void) //Clear the collection
  {
    m_items.clear();
  }
  //Return the number of items in collection
  int Count(void) 
  {
    return m_items.size(); //One Based
  }
  //Operator Returning a reference to TBase
  TBase& operator [](int ItemKey) 
  {
    return m_items[ItemKey];
  }
};