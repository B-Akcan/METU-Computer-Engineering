import re

class Logger:
    def nextline(self):
        pass

class Highlighter:
    def __init__(self, t):
        self.obj = t

    def __getattr__(self, name):
        return getattr(self.obj, name)
    
class HLDate(Highlighter):
    def nextline(self):
        """get next line of log from member object and return
        with replacing all date occurences of 02/12/2015 into **02/12/2015**"""

        next_line = self.obj.nextline()
        return re.sub("(?P<date>(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(0[0-9]*[1-9]|[1-9][0-9]*))", convertDate, next_line)


class HLIP(Highlighter):
    def nextline(self):
        """get next line of log from member object and return
        with replacing all IP occurences like 144.12.1.121 into 144.12.*.*"""

        next_line = self.obj.nextline()
        return re.sub("([0-9]|[1-9][0-9]|[1-9][0-9][0-9])\.([0-9]|[1-9][0-9]|[1-9][0-9][0-9])\.([0-9]|[1-9][0-9]|[1-9][0-9][0-9])\.([1-9][0-9][0-9]|[1-9][0-9]|[0-9])",
                      convertIP,
                      next_line)

def convertDate(m):
    return f"**{m.group('date')}**"

def convertIP(m):
    return f"{m.group(1)}.{m.group(2)}.*.*"

""" a = HLIP(HLDate(Logger()))
b = HLIP(Logger())

l = a.nextline()
while l != ' ':
    print(l)
    l = a.nextline() """

_string = "01/12/2021"
print(re.sub("(?P<date>(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/(0[0-9]*[1-9]|[1-9][0-9]*))", convertDate, _string))

ip = "144.12.1.121"
print(re.sub("([0-9]|[1-9][0-9]|[1-9][0-9][0-9])\.([0-9]|[1-9][0-9]|[1-9][0-9][0-9])\.([0-9]|[1-9][0-9]|[1-9][0-9][0-9])\.([1-9][0-9][0-9]|[1-9][0-9]|[0-9])",
                      convertIP,
                      ip))

# If | operator matches its first operand, it returns (It does not try to match other operands)