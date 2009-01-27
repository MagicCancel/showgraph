/**
 * File: graph.cpp - Graph class implementation, part of
 * Graph library, internal representation of graphs in ShowGraph tool.
 * Copyright (C) 2009  Boris Shurygin
 */
#include "graph_impl.h"

/**
 * Constructor.
 */
Graph::Graph()
{
    node_next_id = 0;
    edge_next_id = 0;
}

/**
 * Creation node in graph
 */
Node *
Graph::NewNode()
{
    /**
     * Check that we have available node id 
     */
    GraphAssert( edge_next_id < GRAPH_MAX_NODE_NUM,
                 GraphError( GRAPH_ERROR_NODE_NUM_OVERFLOW, this));
    NodeListIt it;
    nodes.push_back( NULL);
    it = nodes.end();
    it--;
    Node *node_p = new Node( this, node_next_id++, it);
    *it = node_p;
    return node_p;
}

/**
 * Create edge between two nodes.
 * We do not support creation of edge with undefined endpoints
 */
Edge *
Graph::NewEdge( Node * pred, Node * succ)
{
    /**
     * Check that we have available edge id 
     */
    GraphAssert( edge_next_id < GRAPH_MAX_NODE_NUM,
                 GraphError( GRAPH_ERROR_EDGE_NUM_OVERFLOW, this));
    Edge *edge_p = new Edge( this, edge_next_id++, pred, succ);
    edges.push_back( edge_p);
    EdgeListIt it = edges.end();
    it--;
    edge_p->SetGraphIt( it);

    return edge_p;
}

/**
 * Print graph to stdout in DOT format.
 * Note: Iterates through nodes and edges separately instead
 *       of iterating through nodes and at iterating through edges of each node
 */
void 
Graph::DebugPrint()
{
    Node *n;
    Edge *e;
    out( "digraph{");
    /** Print nodes */
    for (  n = GetFirstNode(); !EndOfNodes(); n = GetNextNode())
    {
        n->DebugPrint();
    }
    /** Print edges */
    for (  e = GetFirstEdge(); !EndOfEdges(); e = GetNextEdge())
    {
        e->DebugPrint();
    }
    out( "}");
}
