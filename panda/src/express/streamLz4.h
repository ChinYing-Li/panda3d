/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file zStream.h
 * @author drose
 * @date 2002-08-05
 */

#ifndef STREAM_LZ4_H
#define STREAM_LZ4_H

#include <memory>

#include "pandabase.h"

// This module is not compiled if lz4 is not available.
#ifdef HAVE_LZ4

#include "streamBase.h"
#include "streamBufLz4.h"

/**
 * An input stream object that uses lz4 to decompress (inflate) the input
 * from another source stream on-the-fly.
 *
 * Attach an IDecompressStream to an existing istream that provides compressed
 * data, and read the corresponding uncompressed data from the
 * IDecompressStream.
 *
 * Seeking is not supported.
 */
class EXPCL_PANDA_EXPRESS IDecompressStreamLz4 : public IDecompressStreamBase {
PUBLISHED:
  INLINE IDecompressStreamLz4();
  INLINE explicit IDecompressStreamLz4(std::istream *source, bool owns_source);

#if _MSC_VER >= 1800
  INLINE IDecompressStreamLz4(const IDecompressStream &copy) = delete;
#endif

  INLINE IDecompressStreamLz4 &open(std::istream *source, bool owns_source);
  INLINE IDecompressStreamLz4 &close();

private:
  StreamBufLz4 _buf;
};

/**
 * An input stream object that uses zlib to compress (deflate) data to another
 * destination stream on-the-fly.
 *
 * Attach an OCompressStream to an existing ostream that will accept
 * compressed data, and write your uncompressed source data to the
 * OCompressStream.
 *
 * Seeking is not supported.
 */
class EXPCL_PANDA_EXPRESS OCompressStreamLz4 : public OCompressStreamBase {
PUBLISHED:
  INLINE OCompressStreamLz4();
  INLINE explicit OCompressStreamLz4(std::ostream *dest, bool owns_dest,
                                  int compression_level = 6);

#if _MSC_VER >= 1800
  INLINE OCompressStreamLz4(const OCompressStream &copy) = delete;
#endif

  INLINE OCompressStreamLz4 &open(std::ostream *dest, bool owns_dest,
                               int compression_level = 6);
  INLINE OCompressStreamLz4 &close();

private:
  StreamBufLz4 _buf;
};

#include "streamLz4.I"

#endif  // HAVE_LZ4


#endif
