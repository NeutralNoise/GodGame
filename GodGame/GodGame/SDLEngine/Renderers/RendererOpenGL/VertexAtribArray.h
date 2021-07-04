/**
 * \file VertexAtribArray.h
 * \author NeutralNoise
 * \brief A vertex attrib array.
 * \version 1.0
 * \date 2021-07-04
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef VERTEX_ATRIB_ARRAY_H_INCLUDED
#define VERTEX_ATRIB_ARRAY_H_INCLUDED

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "../../typedefs.h"


/**
 * \class VertexArray
 * \brief A vertex attrib array.
 * 
*/

class VertexArray
{
public:
	/**
	 * \brief Construct a new VertexArray object
	 * 
	*/
	VertexArray() {};

	/**
	 * \brief Construct a new VertexArray object
	 * 
	 * \param count The number of vertex attrib arrays to create.
	 * \warning count is not used and is not taken into account if greater then 1.
	*/

	VertexArray(const Int32 &count);

	/**
	 * \brief Destroy the VertexArray object
	 * 
	*/

	~VertexArray();

	/**
	 * \brief Add a vertex buffer.
	 * 
	 * \param vb The vertex buffer to add.
	 * \param layout The layout of the vertex buffer.
	 * \see VertexBuffer
	 * \see VertexBufferLayout
	*/

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	/**
	 * \brief Bind the attrib array.
	 * 
	*/

	void Bind() const;

	/**
	 * \brief Unbind the attrib array.
	 * 
	*/

	void Unbind() const;

	/**
	 * \brief Delete the attrib array.
	 * 
	*/

	void DeleteArray();

private:
	UInt32 m_atribArrayID; //!< The ID of the vertex attrib array.
};

#endif //VERTEX_ATRIB_ARRAY_H_INCLUDED
