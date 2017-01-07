import sys
import re

# Read in and structure grammar.
if (len(sys.argv) != 3):
    print('Incorrect number of arguments')
    sys.exit(0)
try:
    stream = open(str(sys.argv[1]))
except FileNotFoundError:
    print('File not found')
    sys.exit(0)
with stream as f:
    grammar = []
    line = f.readline()
    while (line):
        if (line != '\n'): # Do not import blank lines
            nonterminals = []
            terminals = []
            temp = line.replace('\n', '').split('::=')
            rhs = temp[1]
            pattern = '<.*?>' # Non-terminal matching
            reg = re.search(pattern, rhs)
            while(reg):
                nonterminals.append(reg.group(0));
                rhs = rhs[reg.span()[1]:]
                reg = re.search(pattern, rhs)
            pattern = '\".*?\"' # Terminal matching
            reg = re.search(pattern, rhs)
            while(reg):
                terminals.append(reg.group(0).replace('\"', ''));
                rhs = rhs[reg.span()[1]:]
                reg = re.search(pattern, rhs)
        grammar.append({'lhs' : temp[0], 'rhs' : temp[1], 'reduceable' : temp[1][0:1] is '<',
        'nonterminals' : nonterminals, 'terminals' : terminals})
        line = f.readline()
    # Insert artificial rule: s' -> first nontermial
    grammar.insert(0, {'lhs' : '<s\'>', 'rhs' : grammar[0]['lhs'],
    'reduceable' : True, 'nonterminals' : [grammar[0]['lhs']], 'terminals' : []})
if (len(grammar) == 0):
    print('Empty file')
    sys.exit(0)

# We now have a structured grammar formatted from input.
# Define recursive functions for building lr0 items from
# grammar, which is essentially an edge list.

def chain(lhs, grammar, item):
    found = []
    for i in grammar:
        if (i['lhs'] == lhs):
            found.append(i)
    if (len(found) == 0):
        print('There is a problem with your grammar: Cannot find rule for '
        + lhs)
        sys.exit(0)
    for result in found:
        if (not result in item):
            item.append(result)
        if (result['reduceable']):
            chain(result['nonterminals'][0], grammar, item)
    return item

temp = chain(sys.argv[2], grammar, [])
legs = []
for production in temp:
    if (production['reduceable']):
        name = production['nonterminals'][0]
    else:
        name = production['terminals'][0]
    if (not name in legs):
        legs.append(name)
for x in temp:
    print(x['lhs'] + ' -> ' + x['rhs'])
print(legs)
