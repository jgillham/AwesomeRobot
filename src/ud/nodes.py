"""
This module provides a Node and Link class so that a web of interlinked 
 nodes can be created. The web data is contained in a TypedList (called nodes) 
 meaning that it can only contain objects of type Node. If another type is 
 passed to the list a TypeError is raised. 

More information about the classes can be found in their respective 
 documentation.

author -- Josh Gillham
version -- 2-15-13

* Please add yourself as an author if you make a contribution.

Examples:
>>> n1 = Node( 35, 45 )
>>> n2 = Node( 35, 46 )
>>> n3 = Node( 40, 50 )
>>> nodes.append( n1 )
>>> nodes.index( n1 )
0
>>> nodes.append( n2 )
>>> nodes.index( n2 )
1
>>> nodes.append( n3 )
>>> nodes.index( n3 )
2
>>> l1 = Link( n2 )
>>> n1.links.append( l1 )
>>> n1.links.index( l1 )
0
>>> l2 = Link( n1 )
>>> n2.links.append( l2 )
>>> n2.links.index( l2 )
0
>>> l3 = Link( n1 )
>>> n3.links.append( l3 )
>>> n3.links.index( l3 )
0
>>> l4 = Link( n3 )
>>> n1.links.append( l4 )
>>> n1.links.index( l4 )
1
>>> nodes.remove( n1 )
>>> try:
...     n2.links.index( l2 )
...     print "FAILURE"
... except ValueError:
...     print "OK"
OK
>>> try:
...     n3.links.index( l3 )
...     print "FAILURE"
... except ValueError:
...     print "OK"
OK
"""

class TypedList(list):
    """
    The TypedList class provides a list that enforces a class so that only that
     class can be added to the list.

    Instance Members:
        _className -- a private member which holds the type of the class to 
            enforce.

    Examples:
    >>> l = TypedList( int )
    >>> l.append( 1 )
    >>> l.index( 1 )
    0
    >>> l.remove( 1 )
    >>> try:
    ...     l.index( 1 )
    ...     print "FAILURE"
    ... except:
    ...     print "OK"
    OK
    """
    def __init__(self, className ):
        """
        Constructs the class.

        Params:
            className -- is the class to enforce.

        Example:
            >>> isinstance( TypedList( int ), TypedList )
            True
        """
        self._className = className

    def append(self, item):
        """
        Provides a type checked method for adding members to the list.

        Params:
            item -- the item to add to the list.

        Raises:
            TypeError -- if item is not of the type that list was created with.

        Examples:
        >>> l = TypedList( int )
        >>> try:
        ...     l.append( "" )
        ... except TypeError:
        ...     print "OK"
        OK
        >>> i = 1
        >>> l.append( i )
        >>> l.remove( i )
        """
        if __debug__ and not isinstance( item, self._className ):
            raise TypeError, "Bad arguments: Should be a " + \
                self._className.__name__ + " type."
        super( TypedList, self ).append( item ) 
    def remove( self, item ):
        """
        This method provides a type checked method for removing members.

        Params:
            item -- the item to remove from the list.

        Raises:
            TypeError -- when the item is not the type that list was created
              with.
        
        Examples:
        >>> l = TypedList( int )
        >>> try:
        ...     l.remove( "" )
        ... except TypeError:
        ...     print "OK"
        OK
        """
        if __debug__ and not isinstance( item, self._className ):
            raise TypeError, "Bad arguments: Should be a " + \
                self._className.__name__ + " type."
        super( TypedList, self ).remove( item )

class NodeList(TypedList):
    """
    The NodeList class is a list of Node references which provides a "clean"
     method of removing members so that links to that node are also removed.
    """
    def __init__( self ):
        """
        Constructs the class.
        >>> isinstance( NodeList( ), NodeList )
        True
        """
        super( NodeList, self ).__init__( Node )
    def remove( self, item ):
        """
        This method overrides the default method to enforce type checking in
         debugging mode and to also remove links to this node.

        Params:
            item -- is a Node class reference to be removed from the list.

        Raises:
            TypeError -- item is not a Node class.

        Examples:
        >>> l = NodeList( )
        >>> try:
        ...     l.remove( "" )
        ... except TypeError:
        ...     print "OK"
        OK
        """
        if __debug__ and not isinstance( item, self._className ):
            raise TypeError, "Bad arguments: Should be a " + \
                self._className.__name__ + " type."
        for link in item.links:
            for link2 in link.destination.links:
                if link2.destination == item:
                    link.destination.links.remove( link2 )
        super( NodeList, self ).remove( item )

class Node:
    """
    The Node class holds x and y position as well as a list of links to other 
     nodes.

    Instance Members
        pos -- the x and y position of the node.
        links -- a typed list of links.

    Examples:
        >>> n = Node( 1, 2 )
        >>> isinstance( n.pos, XY )
        True
        >>> isinstance( n.links, TypedList )
        True
    """
    def __init__( self, XPos, YPos ):
        """
        Creates the class.

        Params:
            XPos -- the x coordinate.
            YPos -- the y coordinate.
        Examples:
            >>> isinstance( Node( 35, 30 ), Node )
            True
        """
        self.pos = XY( XPos, YPos )
        self.links = TypedList( Link )

class Link:
    """
    The Link class allows a link to be specialized. For example, the robot might
     need to know if the link crosses a log or if the link goes through a narrow
     passage way.

    Instance Members:
        destination -- is a Node class reference to the destination node.

    Examples:
        >>> n = Node( 1, 2 )
        >>> l = Link( n )
        >>> l.destination == n
        True
    """
    def __init__( self, destination ):
        """
        Creates the class.

        Params:
            destination -- is a reference to the destination node.

        Raises:
            TypeError -- when destination is not a Node class.

        Examples:
            >>> isinstance( Link( Node( 2, 2 ) ), Link )
            True
            >>> try:
            ...     Link( 1 )
            ...     print "FAILURE"
            ... except TypeError:
            ...     print "OK"
            OK
        """
        if __debug__ and not isinstance( destination, Node ):
            raise TypeError, "Bad arguments: Should be a Node type."
        self.destination = destination

class XY:
    """
    The XY class holds coordinates for the cartesian plane.
    Instance Members:
        X -- holds the x coordinate.
        Y -- holds the y coordinate.

    Examples:
    >>> l = XY( 1, 3 )
    >>> l.X
    1
    >>> l.Y
    3
    """
    def __init__( self, X, Y ):
        """
        Creates the class.

        Params:
            X -- the x coordinate.
            Y -- the y coordinate.

        Examples:
            >>> isinstance( XY( 1, 2 ), XY )
            True
        """
        self.X = X
        self.Y = Y

nodes = NodeList( )

def printNodes():
    """
    Prints each node and its links.
    """
    for node in nodes:
        print "Node: " + node
        for link in node.links:
            print "Link: " + link.destination
