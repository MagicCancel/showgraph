/**
 * @file: edge_w.h 
 * Edge Widget class definition.
 */
/*
 * GUI for ShowGraph tool.
 * Copyright (C) 2009  Boris Shurygin
 */
#ifndef EDGE_W_H
#define EDGE_W_H

#include "gui_impl.h"
/** size of edge control */
const qreal EdgeControlSize  = 5;

/**
 * Representation of drawable edge
 * @ingroup GUI
 */
class GEdge: public AuxEdge
{
    /** Pointer to corresponding graphics item */
    EdgeItem *item_p;

    /** Default constructor */
    GEdge( GGraph *graph_p, int _id, GNode *_pred, GNode* _succ);
    /** Destructor */
    virtual ~GEdge();

    friend class GraphT< GGraph, GNode, GEdge>;
    friend class NodeT< GGraph, GNode, GEdge>;
    friend class GGraph;
    friend class Node;
public:
    /**
     * Return pointer to graph
     */
    GGraph *graph() const;

    /**
     * Return associated graphics item
     */
    inline EdgeItem *item() const
    {
        return item_p;
    }
    /** 
     * Update DOM element
     */
    virtual void updateElement();

    /**
     * Read properties from XML
     */
    virtual void readFromElement( QDomElement elem);

    /** Overload of setNode from base class */
    inline void setNode( GNode *n, GraphDir dir)
    {
        AuxEdge::setNode( ( AuxNode *)n, dir);
    }
    /** Set predecessor */
    inline void setPred( GNode *n)
    {
        setNode( n, GRAPH_DIR_UP);
    }
    /** Set successor */
    inline void setSucc( GNode *n)
    {
        setNode( n, GRAPH_DIR_DOWN);
    }
    /** Get node in given direction */
    inline GNode *node( GraphDir dir) const;
    /** Get predecessor */
    inline GNode *pred() const 
    {
        return node( GRAPH_DIR_UP);
    }
    /** Get successor */
    inline GNode *succ() const 
    {
        return node( GRAPH_DIR_DOWN);
    }
    /** Next edge in graph's list */
    inline GEdge* nextEdge()
    {
        return static_cast< GEdge *>(AuxEdge::nextEdge());
    }
    /** Next edge in give direction */
    inline GEdge* nextEdgeInDir( GraphDir dir)
    {
        return static_cast< GEdge *>(AuxEdge::nextEdgeInDir( dir));
    }
    /** Next successor */
    inline GEdge* nextSucc()
    {
        return nextEdgeInDir( GRAPH_DIR_DOWN);
    }
    /** Next predecessor */
    inline GEdge* nextPred()
    {
        return nextEdgeInDir( GRAPH_DIR_UP);
    } 
};
/**
 * Graphics item for visualizing a graph edge
 * @ingroup GUI
 */
class EdgeItem: public QGraphicsItem
{
public:        
    /** Modes of an edge */
    typedef enum EdgeMode
    {
        ModeShow,
        ModeEdit
    } EdgeMode;

private:
    /** Graph connection */
    GEdge* edge_p;

    QPointF srcP;
    QPointF cp1;
    QPointF cp2;
    QPointF dstP;
    QPointF topLeft;
    QPointF btmRight;
    EdgeMode curr_mode;
public:
    /** Type of graphics item for edge */
    enum {Type = TypeEdge};
    /** Constructor */
    EdgeItem( GEdge *e_p);
    /** Get item type */
    int type() const
    {
        return Type;
    }
    /** Adjust edge image */
    void adjust();
    /** Get corresponding edge of the graph */
    inline GEdge* edge() const
    {
        return edge_p;    
    }
    /** Get mode */
    inline EdgeMode mode() const
    {
        return curr_mode;
    }
    /** Set mode */
    inline void setMode( EdgeMode m)
    {
        curr_mode = m;
    }
    /** Get bounding rectangle of edge image */
    QRectF boundingRect() const;
    /** Get shape of the edge */
    QPainterPath shape() const;
    /** Event handler for change */
    QVariant itemChange( GraphicsItemChange change, const QVariant &value);
    /** Paint edge */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    /** Event handler for mouse press */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /** Event handler for mouse release */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    /** Event handler for double click */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    /** Get predecessor in terms of graph model */
    inline GNode* pred() const
    {
        return edge()->pred();
    }
    /** Get successor in terms of graph model */
    inline GNode* succ() const
    {
        return edge()->succ();
    }
    /** Remove from scene */
    inline void remove()
    {
        setVisible( false);
        removeFromIndex();
        scene()->removeItem( this);
        edge_p = NULL;
    }
};
#endif