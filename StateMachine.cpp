#include "StateMachine.hpp"

namespace FlappyBirdEngine {
    void StateMachine::addState(StateRef newState, bool isReplacing) {
        _isAdding = true;
        _isReplacing = isReplacing;

        _newState = std::move(newState);
    }

    void StateMachine::removeState() {
        _isRemoving = true;
    }

    void StateMachine::processStateChanges() {
        if (_isRemoving && !_states.empty()) {
            _states.pop();
            _isRemoving = false;
            if (!_states.empty()) {
                _states.top()->resume();
            }
        } else if (_isAdding) {
            _isAdding = false;
            if (!_states.empty()) {
                if (_isReplacing)
                    _states.pop();
                else
                    _states.top()->pause();
            }
            _states.push(std::move(_newState));
            _states.top()->init();
        }
    }

    StateRef& StateMachine::getActiveState() {
        return _states.top();
    }
}