/**
 * @file: mem.h 
 * Some experiments with memory manager
 * @defgroup Mem Memory Manager
 *
 * Implementation of memory manager, In Process of Design&Implementation.
 *
 * Memory manager should solve the following memory-related problems
 * - Dangling pointers. Solution: reference counting via smart pointers
 * - Memory leaks. Solution: Various checks in pools and in pointers
 * - Fragmentation. Solution: Fixed-sized chunks used in pools
 * - Poor locality. Solution: not clear yet :(
 * @ingroup Utils
 */
/*
 * Utils library in Showgraph tool
 * Copyright (C) 2009  Boris Shurygin
 */
#pragma once

#ifndef MEM_H
#define MEM_H

#ifdef _DEBUG
#  define USE_REF_COUNTERS
#endif

#include <QtGlobal>

namespace Mem
{
    /* Class pool predeclaration */
    class Pool;
}
/**
 * Low level functinality for Mem package 
 * @defgroup MemImpl Memory Manager Low Level
 */
namespace MemImpl
{
    /* Predeclaration of mem entry class */
    template < class Data> class Entry;
    /* Predeclaration of chunk class */
    template < class Data> class Chunk;
    /** position in chunk */
    typedef quint8 ChunkPos;
    /** Max number of entries in chunk */
#ifndef MEM_SMALL_CHUNKS
    const quint8 MAX_CHUNK_ENTRIES = ( quint8)( -1);
#else
    const quint8 MAX_CHUNK_ENTRIES = 2;
#endif
    /** 'NULL' equivalent for ChunkPos */
    const ChunkPos UNDEF_POS = MAX_CHUNK_ENTRIES; 
};

#include <stdlib.h>
#include "mem_ref.h" /** Memory reference */
#include "mem_obj.h" /** Memory object base class */
#include "mem_chunk.h" /** Memory chunk class */
#include "mem_pool.h" /** Memory pool */
#include "mem_entry.h" /** Memory entry class */
#include "mem_fixed_pool.h" /** Memory pool */

#endif /* MEM_H */