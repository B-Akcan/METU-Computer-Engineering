class StackEmptyException(Exception):
    pass

class my_stack:
  def __init__(self):
    self._stack = []

def check_input_type(inp):
  if not isinstance(inp, my_stack):
    raise TypeError('Expected stack; got %s' % type(inp).__name__)

def push(item, st:my_stack):
  check_input_type(st)
  st._stack.append(item)

def pop(st:my_stack):
  check_input_type(st)
  to_return = None
  try:
    to_return = st._stack[-1]
    st._stack = st._stack[:-1]
  except IndexError:
    raise StackEmptyException("Stack is empty") from None
  return to_return

def top(st:my_stack):
  check_input_type(st)
  to_return = None
  try:
    to_return = st._stack[-1]
  except IndexError:
    raise StackEmptyException("Stack is empty") from None
  return to_return

def is_empty(st:my_stack):
  check_input_type(st)
  return len(st._stack) == 0

def create_stack():
  return my_stack()
