#include "IComponent.h"
#include <typeinfo>

IComponent::IComponent(Entity& entity) : ParentEntity(entity)
{

}

IComponent::~IComponent()
{
}
