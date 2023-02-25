#include <vector>
#include <random>
#include <iostream>

#include "gate.h"
#include "wire.h"

Gate::Gate(int num_inputs, Wire* output) 
	: m_output(output), m_inputs(num_inputs), m_delay(0), m_current_state('X')
{
    
}

Gate::~Gate(){}

void Gate::wireInput(unsigned int id, Wire* in)
{
    if(id < m_inputs.size())
    {
        m_inputs[id] = in;
    }
}

And2Gate::And2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* And2Gate::update(uint64_t current_time)
{
    
  char state = '1';
  Event* e = nullptr;
	for(auto w : m_inputs)
	{
		char in = w->getState();
		if(in == '0')
		{
			state = '0';
			break;
		}
		else if(in == 'X')
		{
			state = 'X';
		}
	}
    if(state != m_current_state)
	{
    m_current_state = state;
    uint64_t next = current_time + m_delay;
		e = new Event {next,m_output,state};
         
	}
    return e;
}

Or2Gate::Or2Gate(Wire* a, Wire* b, Wire* o) : Gate(2,o)
{
    wireInput(0,a);
    wireInput(1,b);
}

Event* And2Gate::update(uint64_t current_time) {
    return updateRecursive(current_time, '1');
}

Event* And2Gate::updateRecursive(uint64_t current_time, char state) {
    bool allInputsSet = true;
    for(auto w : m_inputs)
    {
        char in = w->getState();
        if(in == '0')
        {
            state = '0';
            allInputsSet = false;
            break;
        }
        else if(in == 'X')
        {
            state = 'X';
            allInputsSet = false;
        }
    }

    if (allInputsSet) {
        if(state != m_current_state) {
            m_current_state = state;
            uint64_t next = current_time + m_delay;
            return new Event {next, m_output, state};
        }
        else {
            return nullptr;
        }
    }
    else {
        return updateRecursive(current_time, state);
    }
}


NotGate::NotGate(Wire* a, Wire* o) : Gate(1,o) {
   wireInput(0,a);
}

char NotGate::computeOutputState(int inputIndex) {
  if (inputIndex >= m_inputs.size()) {
    return '0';
  }

  char in = m_inputs[inputIndex]->getState();

  if (in == '0') {
    return '0';
  }
  else if (in == 'X') {
    return 'X';
  }
  else if (in == '1') {
    return '0';
  }

  return '0';
}

Event* NotGate::update(uint64_t current_time) {
  char newState = computeOutputState(0);
  char prevState = m_current_state;

  if (newState != prevState) {
    m_current_state = newState;
    uint64_t next = current_time + m_delay;
    return new Event {next, m_output, newState};
  }

  return nullptr;
}



