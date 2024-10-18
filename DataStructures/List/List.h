#pragma once

#include <cassert>
#include <xmemory>

#define NODISCARD [[nodiscard]]
#define FORCEINLINE __forceinline

namespace List
{
	namespace Private
	{
		template<typename ElementType>
		struct ListNode final
		{
			ListNode* Next = nullptr;
			ListNode* Previous = nullptr;

			ElementType Data;
		};
	}

	template<typename MyListType>
	class ConstIterator
	{
	public:
		using PointerType = typename MyListType::ConstPointerType;
		using ReferenceType = typename MyListType::ConstReferenceType;
		using ListNodeType = typename MyListType::ListNodeType;

		ConstIterator(ListNodeType* const BeginNode, ListNodeType* const EndNode)
			: BeginNode(BeginNode)
			, CurrentNode(BeginNode)
			, EndNode(EndNode)
		{
		}

		NODISCARD FORCEINLINE ReferenceType operator*() const
		{
			assert(CurrentNode != EndNode && "Dereferencing End Iterator of LinkedList");

			return CurrentNode->Data;
		}

		NODISCARD FORCEINLINE PointerType operator->() const
		{
			assert(CurrentNode != EndNode && "Dereferencing End Iterator of LinkedList");

			return &CurrentNode->Data;
		}

		FORCEINLINE ConstIterator& operator++()
		{
			assert(CurrentNode != EndNode && "Cannot increment End Iterator of LinkedList");

			CurrentNode = CurrentNode->Next;
			return *this;
		}

		FORCEINLINE ConstIterator operator++(int)
		{
			assert(CurrentNode != EndNode && "Cannot increment End Iterator of LinkedList");

			ConstIterator Temp = *this;
			CurrentNode = CurrentNode->Next;
			return Temp;
		}

		FORCEINLINE ConstIterator& operator--()
		{
			ListNodeType* const Previous = CurrentNode->Previous;

			assert(Previous != EndNode && "Cannot decrement Begin Iterator of LinkedList");

			CurrentNode = Previous;
			return *this;
		}

		FORCEINLINE ConstIterator operator--(int)
		{
			ConstIterator Temp = *this;
			--*this;
			return Temp;
		}

		NODISCARD FORCEINLINE bool operator==(const ConstIterator& Other) const
		{
			return CurrentNode == Other.CurrentNode;
		}

		NODISCARD FORCEINLINE bool operator!=(const ConstIterator& Other) const
		{
			return CurrentNode != Other.CurrentNode;
		}

	protected:
		ListNodeType* BeginNode;
		ListNodeType* CurrentNode;
		ListNodeType* EndNode;
	};

	template<typename MyListType>
	class Iterator final : public ConstIterator<MyListType>
	{
	public:
		using Super = ConstIterator<MyListType>;
		using PointerType = typename MyListType::PointerType;
		using ReferenceType = typename MyListType::ReferenceType;
		using ListNodeType = typename MyListType::ListNodeType;

		Iterator(ListNodeType* const BeginNode, ListNodeType* const EndNode)
			: Super(BeginNode, EndNode)
		{
		}

		NODISCARD FORCEINLINE ReferenceType operator*() noexcept
		{
			return const_cast<ReferenceType>(Super::operator*());
		}

		NODISCARD FORCEINLINE PointerType operator->() noexcept
		{
			return &(**this);
		}

		FORCEINLINE Iterator& operator++() noexcept
		{
			Super::operator++();
			return *this;
		}

		FORCEINLINE Iterator operator++(int) noexcept
		{
			Iterator Temp = *this;
			Super::operator++();
			return Temp;
		}

		FORCEINLINE Iterator& operator--() noexcept
		{
			Super::operator--();
			return *this;
		}

		FORCEINLINE Iterator operator--(int) noexcept
		{
			Iterator Temp = *this;
			Super::operator--();
			return Temp;
		}
	};

	//template<typename IteratorType>
	//class ReverseIterator final
	//{
	//public:
	//	using PointerType = typename IteratorType::PointerType;
	//	using ReferenceType = typename IteratorType::ReferenceType;
	//	using ListNodeType = typename IteratorType::ListNodeType;
	//
	//	ReverseIterator(ListNodeType* const BeginNode, ListNodeType* const EndNode)
	//		: Iterator(BeginNode, EndNode)
	//	{
	//	}
	//
	//	NODISCARD FORCEINLINE ReferenceType operator*() noexcept
	//	{
	//		IteratorType TempIterator = Iterator;
	//		--TempIterator;
	//
	//		if constexpr (std::is_pointer_v<IteratorType>)
	//		{
	//			return TempIterator;
	//		}
	//		else
	//		{
	//			return *TempIterator.operator->();
	//		}
	//	}
	//
	//	NODISCARD FORCEINLINE PointerType operator->() noexcept
	//	{
	//		IteratorType TempIterator = Iterator;
	//		return *--Iterator;
	//	}
	//
	//	FORCEINLINE ReverseIterator& operator++() noexcept
	//	{
	//		--Iterator;
	//		return *this;
	//	}
	//
	//	FORCEINLINE ReverseIterator operator++(int) noexcept
	//	{
	//		IteratorType TempIterator = Iterator;
	//		--Iterator;
	//		return TempIterator;
	//	}
	//
	//	FORCEINLINE ReverseIterator& operator--() noexcept
	//	{
	//		++Iterator;
	//		return *this;
	//	}
	//
	//	FORCEINLINE ReverseIterator operator--(int) noexcept
	//	{
	//		ReverseIterator TempIterator = *this;
	//		++Iterator;
	//		return TempIterator;
	//	}
	//
	//	const IteratorType& GetUnderlyingIterator() const noexcept
	//	{
	//		return Iterator;
	//	}
	//
	//private:
	//	IteratorType Iterator{};
	//};

	//template<typename FirstIteratorType, typename SecondIteratorType>
	//NODISCARD FORCEINLINE bool operator==(const ReverseIterator<FirstIteratorType>& First, const ReverseIterator<SecondIteratorType>& Second) noexcept
	//{
	//	return First.GetUnderlyingIterator() == Second.GetUnderlyingIterator();
	//}
	//
	//template<typename FirstIteratorType, typename SecondIteratorType>
	//NODISCARD FORCEINLINE bool operator!=(const ReverseIterator<FirstIteratorType>& First, const ReverseIterator<SecondIteratorType>& Second) noexcept
	//{
	//	return First.GetUnderlyingIterator() != Second.GetUnderlyingIterator();
	//}

	template<typename ElementType, typename AllocatorType = std::allocator<ElementType>>
	class LinkedList
	{
	public:
		using ListNodeType = Private::ListNode<ElementType>;

		using AllocatorElementType = AllocatorType;
		using AllocatorNodeType = typename std::allocator_traits<AllocatorElementType>::template rebind_alloc<ListNodeType>;

		using PointerType = ElementType*;
		using ConstPointerType = const ElementType*;
		using ReferenceType = ElementType&;
		using ConstReferenceType = const ElementType&;

		using IteratorType = Iterator<LinkedList>;
		using ConstIteratorType = ConstIterator<LinkedList>;
		//using ReverseIteratorType = ReverseIterator<IteratorType>;
		//using ConstReverseIteratorType = ReverseIterator<ConstIteratorType>;

		LinkedList()
		{
			EndNode = AllocatorNode.allocate(1);
			EndNode->Next = nullptr;
			EndNode->Previous = nullptr;
		}

		LinkedList(std::initializer_list<ElementType> Values)
			: LinkedList()
		{
			for (const ElementType& Value : Values)
			{
				PushBack(Value);
			}
		}

		explicit LinkedList(const AllocatorType& Allocator)
			: AllocatorElement(Allocator)
			, LinkedList()
		{
		}

		explicit LinkedList(const size_t Count)
			: LinkedList()
		{
			for (size_t i = 0; i < Count; ++i)
			{
				PushBack({});
			}
		}

		explicit LinkedList(const size_t Count, const AllocatorType& Allocator)
			: AllocatorElement(Allocator)
			, LinkedList()
		{
			for (size_t i = 0; i < Count; ++i)
			{
				PushBack({});
			}
		}

		explicit LinkedList(const size_t Count, ElementType&& Value)
			: LinkedList()
		{
			for (size_t i = 0; i < Count; ++i)
			{
				PushBack(std::forward<ElementType>(Value));
			}
		}

		explicit LinkedList(const size_t Count, ElementType&& Value, const AllocatorElementType& Allocator)
			: AllocatorElement(Allocator)
			, LinkedList()
		{
			for (size_t i = 0; i < Count; ++i)
			{
				PushBack(std::forward<ElementType>(Value));
			}
		}

		~LinkedList()
		{
			Clear();
			AllocatorNode.deallocate(EndNode, 1);
		}

		NODISCARD FORCEINLINE size_t GetSize() const
		{
			return Size;
		}

		NODISCARD FORCEINLINE ConstReferenceType Front() const
		{
			assert(Size && "Front() called on empty LinkedList");

			return Head->Data;
		}

		NODISCARD FORCEINLINE ReferenceType Front()
		{
			assert(Size && "Front() called on empty LinkedList");

			return Head->Data;
		}

		NODISCARD FORCEINLINE ConstReferenceType Back() const
		{
			assert(Size && "Back() called on empty LinkedList");

			return Tail->Data;
		}

		NODISCARD FORCEINLINE ReferenceType Back()
		{
			assert(Size && "Back() called on empty LinkedList");

			return Tail->Data;
		}

		NODISCARD FORCEINLINE ConstIteratorType Begin() const
		{
			return ConstIteratorType(Head, EndNode);
		}

		NODISCARD FORCEINLINE IteratorType Begin()
		{
			return IteratorType(Head, EndNode);
		}

		NODISCARD FORCEINLINE ConstIteratorType ConstBegin() const
		{
			return Begin();
		}

		//NODISCARD FORCEINLINE ConstReverseIteratorType ReverseBegin() const
		//{
		//	return ConstReverseIteratorType(EndNode, EndNode);
		//}
		//
		//NODISCARD FORCEINLINE ReverseIteratorType ReverseBegin()
		//{
		//	return ReverseIteratorType(EndNode, EndNode);
		//}
		//
		//NODISCARD FORCEINLINE ConstReverseIteratorType ConstReverseBegin() const
		//{
		//	return ReverseBegin();
		//}

		NODISCARD FORCEINLINE ConstIteratorType End() const
		{
			return ConstIteratorType(EndNode, EndNode);
		}

		NODISCARD FORCEINLINE IteratorType End()
		{
			return IteratorType(EndNode, EndNode);
		}

		NODISCARD FORCEINLINE ConstIteratorType ConstEnd() const
		{
			return End();
		}

		//NODISCARD FORCEINLINE ConstReverseIteratorType ReverseEnd() const
		//{
		//	return ConstReverseIteratorType(EndNode, EndNode);
		//}

		//NODISCARD FORCEINLINE ReverseIteratorType ReverseEnd()
		//{
		//	return ReverseIteratorType(EndNode, EndNode);
		//}

		//NODISCARD FORCEINLINE ConstReverseIteratorType ConstReverseEnd() const
		//{
		//	return ReverseEnd();
		//}

		template<typename... ArgTypes>
		void EmplaceFront(ArgTypes&&... Args)
		{
			ListNodeType* NewNode = AllocatorNode.allocate(1);
			AllocatorElement.construct(&NewNode->Data, std::forward<ArgTypes>(Args)...);

			if (!Size)
			{
				Head = NewNode;
				Head->Previous = EndNode;
				Tail = Head;
				Tail->Next = EndNode;
				EndNode->Previous = Tail;
			}
			else
			{
				NewNode->Next = Head;
				NewNode->Previous = EndNode;
				Head->Previous = NewNode;
				Head = NewNode;
			}

			EndNode->Next = Head;

			++Size;
		}

		template<typename... ArgTypes>
		void EmplaceBack(ArgTypes&&... Args)
		{
			ListNodeType* NewNode = AllocatorNode.allocate(1);
			AllocatorElement.construct(&NewNode->Data, std::forward<ArgTypes>(Args)...);

			if (!Size)
			{
				Head = NewNode;
				Head->Previous = EndNode;
				Tail = Head;
				Tail->Next = EndNode;
				EndNode->Next = Head;
			}
			else
			{
				NewNode->Next = EndNode;
				NewNode->Previous = Tail;
				Tail->Next = NewNode;
				Tail = NewNode;
			}

			EndNode->Previous = Tail;

			++Size;
		}

		void PushFront(ElementType&& Value)
		{
			EmplaceFront(std::move(Value));
		}

		void PushFront(ConstReferenceType Value)
		{
			EmplaceFront(Value);
		}

		void PushBack(ElementType&& Value)
		{
			EmplaceBack(std::move(Value));
		}

		void PushBack(ConstReferenceType Value)
		{
			EmplaceBack(Value);
		}

		void PopFront()
		{
			assert(Size && "PopFront() called on empty LinkedList");

			ListNodeType* Next = Head->Next;

			AllocatorElement.destroy(&Head->Data);
			AllocatorNode.deallocate(Head, 1);

			Head = Next;
			Head->Previous = EndNode;
			EndNode->Next = Head;

			--Size;
		}

		void PopBack()
		{
			assert(Size && "PopBack() called on empty LinkedList");

			ListNodeType* Previous = Tail->Previous;

			AllocatorElement.destroy(&Tail->Data);
			AllocatorNode.deallocate(Tail, 1);

			Tail = Previous;
			Tail->Next = EndNode;
			EndNode->Previous = Tail;

			--Size;
		}

		void Clear()
		{
			if (!Size) return;

			ListNodeType* Current = Head;
			ListNodeType* Next = nullptr;

			while (Current != EndNode)
			{
				Next = Current->Next;
				AllocatorElement.destroy(&Current->Data);
				AllocatorNode.deallocate(Current, 1);
				Current = Next;
			}

			Size = 0;

			Head = EndNode;
			Tail = EndNode;
			EndNode->Next = nullptr;
			EndNode->Previous = nullptr;
		}

	private:
		AllocatorType AllocatorElement = {};
		AllocatorNodeType AllocatorNode = {};

		ListNodeType* Head = nullptr;
		ListNodeType* Tail = nullptr;
		ListNodeType* EndNode;

		size_t Size = 0;
	};
}
