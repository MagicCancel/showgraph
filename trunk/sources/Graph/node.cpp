/**
 * File: node.cpp - Node class implementation, part of Graph library, 
 * an internal representation of graphs in ShowGraph tool.
 * Copyright (C) 2009  Boris Shurygin
 */

/** 
 * Destructor. Corrects list of nodes in corresponding graph and deletes adjacent edges
 */
template <class Graph, class Node, class Edge>
NodeT<Graph, Node, Edge>::~NodeT()
{
    Edge *edge;
    
    /** Delete incidient edges */
    for ( edge = firstSucc(); IsNotNullP( edge);)
    {
        Edge* next = edge->nextSucc();
        edge->DetachFromNode( GRAPH_DIR_DOWN);// Edge is detached from succ node
        delete edge;
        edge = next;
    }
    for ( edge = firstPred(); IsNotNullP( edge);)
    {
        Edge* next = edge->nextPred();
        edge->DetachFromNode( GRAPH_DIR_UP);// Edge is detached from pred node
        delete edge;
        edge = next;
    }
    
    element.parentNode().removeChild( element);

    /** Delete myself from graph */
    graph_p->DeleteNode( &my_it);
}

/**
 * Add an edge to this node in specified direction
 */
template <class Graph, class Node, class Edge>
void
NodeT<Graph, Node, Edge>::AddEdgeInDir( Edge *edge, GraphDir dir)
{
    assert( IsNotNullP( edge));
    EdgeListIt *it = edge->GetNodeIt( RevDir( dir));
    if ( IsNotNullP( first_edge[ dir]))
    {
        it->Attach( first_edge[ dir]->GetNodeIt( RevDir( dir)));
    }
    first_edge[ dir] = edge;
}

/**
 * Delete edge pointed by iterator in specidied direction
 */
template <class Graph, class Node, class Edge>
void
NodeT<Graph, Node, Edge>::DeleteEdgeInDir( GraphDir dir, Edge* edge)
{
    assert( IsNotNullP( edge));
    if( first_edge[ dir] == edge)
    {
        first_edge[ dir] = edge->nextEdgeInDir( dir);
    }
}

/**
 * Print node in Dot format to stdout
 */
template <class Graph, class Node, class Edge>
void
NodeT<Graph, Node, Edge>::DebugPrint()
{
    out("%u;", id());
}

/**
 * Update DOM tree element
 */
template <class Graph, class Node, class Edge>
void
NodeT<Graph, Node, Edge>::updateElement()
{
    element.setAttribute( "id", id());
}

/**
 * read properties from DOM tree element
 */
template <class Graph, class Node, class Edge>
void
NodeT<Graph, Node, Edge>::readFromElement( QDomElement e)
{
    element = e;
}