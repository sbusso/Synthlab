//
//  Event.cpp
//  Synthlab - App
//
//  Created by Matthias Pueski on 05.04.18.
//

#include "Event.h"

Event::Event() {
    
}

Event::Event(Event* e){
    this->name = e->getName();
    this->type = e->getType();
    this->value = e->getValue();
}

Event::Event(String name, Type type) {
    this->name = name;
    this->type = type;
}

Event::~Event() {
    
}

String Event::getName() {
    return name;
}

Event::Type Event::getType() {
    return type;
}

void Event::setValue(int value) {
    this->value = value;
}

int Event::getValue() {
    return value;
}
