/**
 * \file IndexBuffer.h
 * \author NeutralNoise
 * \brief A buffer of indices.
 * \version 1.0
 * \date 2021-07-03
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef INDEX_BUFFER_H_INCLUDED
#define INDEX_BUFFER_H_INCLUDED
#include "../../typedefs.h"

/**
 * \class IndexBuffer
 * \brief Describes a buffer of indices.
 * 
*/

class IndexBuffer
{
public:

	/**
	 * \brief Construct a new IndexBuffer object
	 * 
	*/

	IndexBuffer();

	/**
	 * \brief Construct a new IndexBuffer object
	 * 
	 * \param indices The indiecs data to upload to the GPU.
	 * \param count The number of elements in the buffer.
	*/

	IndexBuffer(const UInt32 *indices, const UInt32 &count);

	/**
	 * \brief Destroy the IndexBuffer object
	 * 
	*/

	~IndexBuffer();

	/**
	 * \brief Bind the Index buffer.
	 * 
	*/

	void Bind() const;

	/**
	 * \brief Unbind the index buffer.
	 * 
	*/

	void Unbind() const;

	/**
	 * \brief Upload the index buffer to the GPU.
	 * 
	 * \param indices The data to be uploaded to the GPU
	 * \param count The number of elements to upload.
	*/

	void SetData(const UInt32 * indices, const UInt32 &count);

	/**
	 * \brief Delete the buffer.
	 * 
	*/

	void DeleteBuffer();

	/**
	 * \brief Get the size of the buffer.
	 * 
	 * \return UInt32 Returns the size of the buffer in bytes.
	*/

	inline UInt32 GetCount() const { return m_Count; }

private:
	UInt32 m_indexBufferID; //!< The ID of the buffer.
	UInt32 m_Count; //!< The maximum number of elements in the buffer.
};

#endif //INDEX_BUFFER_H_INCLUDED
