#pragma once

#include <cstdint>
#include <vector>

namespace UTE
{

	enum class EVertexDataType : uint8_t
	{
		Byte,
		Short,
		Int,
		Float,
		Double
	};

	inline uint32_t GetVertexDataTypeSize(EVertexDataType DataType)
	{
		switch (DataType)
		{
			case EVertexDataType::Byte:
			{
				return sizeof(char);
			}

			case EVertexDataType::Short:
			{
				return sizeof(short);
			}

			case EVertexDataType::Int:
			{
				return sizeof(int);
			}

			case EVertexDataType::Float:
			{
				return sizeof(float);
			}

			case EVertexDataType::Double:
			{
				return sizeof(double);
			}
		}

		return 0;
	}

	struct VertexElement
	{
		EVertexDataType DataType;
		uint8_t Components = 1;
		uint32_t Size = 0;
		uint32_t Offset = 0;
	};

	struct VertexLayout
	{

	public:

		/*-----Functions-----*/

		/*Adds a new element to the vertex layout.*/
		void AddElementToLayout(EVertexDataType DataType, uint8_t Components);

		/*Sets the element at the specified index to a new element.*/
		bool SetElementAtIndex(uint32_t Index, EVertexDataType DataType, uint8_t Components);

		/*Removes the element at the specified index.*/
		bool RemoveElementAtIndex(uint32_t Index);

		/*Returns the total size of the vertex layout*/
		uint32_t GetVertexStride() const;

		/*Returns the offset of the specified element in bytes.*/
		bool GetOffsetAtIndex(uint32_t Index, uint32_t* OutOffset) const;

		/*Returns the number of elements within the layout.*/
		uint32_t GetNumElements() const;

		/*Returns the element at the specified index.*/
		const VertexElement& GetElementAtIndex(uint32_t Index) const;

	private:

		/*Returns if the specfied index exists.*/
		bool IsValidElement(uint32_t Index) const;

		/*Refreshes the offset of all registered elements.*/
		void RefreshElementOffsets();

		/*Refreshes the total size of the vertex layout*/
		void RefreshVertexStride();

		/*-----Variables-----*/

		/*The total size of the vertex layout.*/
		uint32_t mVertexStride = 0;

		/*List of all registered elements within the layout.*/
		std::vector<VertexElement> mElementList;
		
	};

}