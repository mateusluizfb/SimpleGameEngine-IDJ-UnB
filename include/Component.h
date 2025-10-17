#ifndef COMPONENT_H
#define COMPONENT_H

/*
Notes: 
- virtual makes the method possible to override (polymorphism)
- "= 0" makes it required for the method be implemented, and this class becomes abstract, so it cannot be instantiated 
- `class GameObject` is needed in order to "forward declare" that his class exists, but it's going to me implemented later 
*/

class GameObject;

class Component {
protected:
  GameObject& associated;

public:
  // Notes: Child classes must define their own constructor, but they must call this
  // base constructor in the initialization list. In C++, constructors are not inherited.
  Component(GameObject &associated);
  virtual ~Component();

  virtual void Start();
  virtual void Update(float dt) = 0;
  virtual void Render() = 0;
  virtual void NotifyCollision(GameObject &other);
};

#endif
