/**
 * File: graph_w.h - Graph Widget class definition.
 * GUI for ShowGraph tool.
 * Copyright (C) 2009  Boris Shurygin
 */
#ifndef GRAPH_W_H
#define GRAPH_W_H

#include "gui_impl.h"

class GraphView: public AuxGraph, public QGraphicsView
{
    QPoint src;
    QPoint dst;
    bool createEdge;
    NodeItem *tmpSrc;
public:
    /** Constructor */
    GraphView();
    ~GraphView();

    void drawBackground(QPainter *painter, const QRectF &rect);
    
    /** New node/edge overloads */
    NodeItem* newNode();
    NodeItem* newNode( QDomElement e);
    EdgeItem* newEdge( NodeItem* pred, NodeItem* succ);
    EdgeItem* newEdge( NodeItem* pred, NodeItem* succ, QDomElement e);
    
    AuxEdge* newEdge( AuxNode * pred, AuxNode *succ)
    {
        return ( AuxEdge*)newEdge( static_cast< NodeItem *>( pred),
                                    static_cast< NodeItem *> (succ));
    }
    AuxEdge* newEdge( AuxNode * pred, AuxNode *succ, QDomElement e)
    {
        return ( AuxEdge*)newEdge( static_cast< NodeItem *>( pred),
                                    static_cast< NodeItem *> (succ), e);
    }

    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void drawForeground(QPainter *painter, const QRectF &rect);
    
    inline bool IsCreateEdge() const
    {
        return createEdge;
    }
    inline void SetCreateEdge( bool val)
    {
        createEdge = val;
    }
    inline void SetTmpSrc( NodeItem* node)
    {
        tmpSrc = node;
    }
    inline NodeItem* GetTmpSrc()
    {
        return tmpSrc;
    }

    /** Graph part */
    virtual void * CreateNode( AuxGraph *graph_p, int _id)
    {
        NodeItem* node_p = new NodeItem( static_cast<GraphView *>(graph_p), _id);
        return node_p;
    }
    virtual void * CreateEdge( AuxGraph *graph_p, int _id, AuxNode *_pred, AuxNode* _succ)
    {
        return new EdgeItem(  static_cast<GraphView *>( graph_p), _id,
                              static_cast<NodeItem *>( _pred), 
                              static_cast<NodeItem *>( _succ));
    }

    inline EdgeItem* firstEdge() 
    {
        return static_cast< EdgeItem *>( AuxGraph::firstEdge());
    }
    inline NodeItem* firstNode()
    {
        return static_cast< NodeItem *>( AuxGraph::firstNode());
    }
    void doLayout()
    {
        AuxGraph::doLayout();
        for ( NodeItem* n = firstNode();
              isNotNullP( n);
              n = n->nextNode())
        {
            n->setPos( n->modelX(), n->modelY());
        }
    }
};

#endif