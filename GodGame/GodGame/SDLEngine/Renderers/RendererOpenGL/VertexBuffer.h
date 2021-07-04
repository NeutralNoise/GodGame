/**
 * \file VertexBuffer.h
 * \author NeutralNoise
 * \brief A vertex buffer to upload vertex data to the GPU.
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef VERTEX_BUFFER_H_INCLUDED
#define VERTEX_BUFFER_H_INCLUDED
#include "../../typedefs.h"

/**
 * \class VertexBuffer
 * \brief Describes a vertex buffer.
 * 
*/

class VertexBuffer
{
public:

  /**
   * \brief Construct a new VertexBuffer object
   * 
  */

  VertexBuffer(); // This does nothing 

  /**
   * \brief Construct a new VertexBuffer object
   * 
   * \param data The data to pass to the vertex buffer.
   * \param size The size the buffer in bytes.
  */

  VertexBuffer(const void *data, const UInt32 &size);

  /**
   * \brief Destroy the VertexBuffer object
   * 
  */

  ~VertexBuffer();

  /**
   * \brief Bind the vertex buffer.
   * 
  */

  void Bind() const;

  /**
   * \brief Unbind the vertex buffer.
   * 
  */

  void Unbind() const;

  /**
   * \brief Set the data of the vertex array.
   * 
   * \param data The data to send too the GPU.
   * \param size The size of the data in bytes.
  */

  void SetData(const void *data, const UInt32 &size);

  /**
   * \brief Delete the buffer.
   * 
  */

  void DeleteBuffer();

private:
    UInt32 m_bufferID; //!< The ID of the buffer.
};



#endif //VERTEX_BUFFER_H_INCLUDED
