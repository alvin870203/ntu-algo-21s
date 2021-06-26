import networkx as nx

filename = 'public_case_8'

with open('inputs/' + filename + '.in') as f:
    lines = f.readlines()

dir_type = lines[0].strip()
n = int(lines[1].strip())
print(n)
# print(lines)
originalList = [line.strip().split()[0:2] for line in lines[3:-1]]
# print(originalList)

with open('outputs/' + filename + '.out') as f:
    lines = f.readlines()[1:]

breakList = [line.strip().split()[0:2] for line in lines]
# print(breakList)

remainList = [edge for edge in originalList if edge not in breakList]
# print(remainList)

if dir_type == 'u':
    originalG = nx.Graph()
    remainG = nx.Graph()
elif dir_type == 'd':
    originalG = nx.DiGraph()
    remainG = nx.DiGraph()
else:
    print("Wrong Dir Type!")

originalG.add_edges_from(originalList)
remainG.add_edges_from(remainList)

print(f'nodes number correct: {len(remainG.nodes()) == n}')
# print(remainG.edges())

try:
    print(sum(1 for c in nx.find_cycle(originalG)))
    for cycle in nx.find_cycle(originalG):
        print(cycle)
except:
    print(0)

try:
    print(sum(1 for c in nx.find_cycle(remainG)))
    for cycle in nx.find_cycle(remainG):
        print(cycle)
except:
    print(0)