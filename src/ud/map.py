class Node:
	destinations = []
	directional = False
	position = None
	def __init__( self, XPos, YPos ):
		self.pos = XY( XPos, YPos )
                self.links = []
	
class Link:
	type = None
	distance = None
	def __init__( self, dest ):
		self.destination = dest
	
class XY:
	def __init__( self, X, Y ):
		self.X = X
		self.Y = Y
nodes = []
nodes.append( Node( 35, 40 ) )
nodes.append( Node( 35, 45 ) )
nodes.append( Node( 35, 45 ) )
nodes[0].name = "Bob"
nodes[1].name = "Sally"
nodes[2].name = "Susan"
nodes[0].links.append( Link( nodes[1] ) )

nodes[1].links.append( Link( nodes[0] ) )
nodes[2].links.append( Link( nodes[0] ) )
nodes[0].links.append( Link( nodes[2] ) )

for node in nodes:
	print "Node: " + node.name
        for link in node.links:
        	print link.destination.name


def remove( index ):
        for link in nodes[index].links:
        	for link2 in link.destination.links:
        		if link2.destination == nodes[index]:
        			link.destination.links.remove( link2 )
        nodes.remove( nodes[index] )
remove( 0 )

print "Final::"
for node in nodes:
	print "Node: " + node.name
        for link in node.links:
        	print link.destination.name
