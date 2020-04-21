#ifndef CUSTOM_MEMORY_MANAGER
#define CUSTOM_MEMORY_MANAGER

#include <cstdlib>
#include <stdexcept>
#include <iostream>

class AllocatorSingleton;
class Allocator;
class FirstFitAllocator;
class BestFitAllocator;
class CustomFitAllocator;



class Allocator{
	protected:
		struct MemoryBlock{
			void* location;
			size_t size;
			bool reserved = false;
			MemoryBlock* prev = nullptr;
			MemoryBlock* next = nullptr;

			void alloc(size_t);
			void dealloc();

			//redefine typical allocation operators for use in bookkeeper
			static void* operator new(size_t);
			static void operator delete(void*);
		};

		void* memory = malloc((256 * 1024 * 1024) + (32 * 1024));
		MemoryBlock* memlist = new MemoryBlock{memory, (256 * 1024 * 1024) + (32 * 1024)};

	public:
		void print_blocks();
		virtual void* allocate(size_t);
		virtual void deallocate(void*);
};

void Allocator::MemoryBlock::alloc(size_t size){
	reserved = true;
	if(this->size < size)
		throw std::bad_alloc();
	if(this->size > size){
		void* location_of_new_block = ((char*)location) + size;
		size_t size_of_new_block = this->size - size;
		MemoryBlock* prev_of_new_block = this;
		MemoryBlock* next_of_new_block = next;
		next = new MemoryBlock{location_of_new_block, size_of_new_block, false, prev_of_new_block, next_of_new_block};
		this->size = size;
		if(next_of_new_block != nullptr)
			next->next->prev = next;	
	}
}

void Allocator::MemoryBlock::dealloc(){
	reserved = false;
	if(next != nullptr){
		if(!next->reserved){
			MemoryBlock* temp = next;
			size += temp->size;
			next = temp->next;
			if(next != nullptr)
				next->prev = this;
			delete temp;
		}
	}
	if(prev != nullptr){
		if(!prev->reserved){
			prev->size += size;
			prev->next = next;
			if(next != nullptr)
				next->prev = prev;
			delete this;
		}
	}
}

void* Allocator::MemoryBlock::operator new(size_t size){
	return malloc(size);
}

void Allocator::MemoryBlock::operator delete(void* pointer){
	free(pointer);
}

void* Allocator::allocate(size_t size){
	return malloc(size);
}

void Allocator::deallocate(void* pointer){
	free(pointer);
}

void Allocator::print_blocks(){
	MemoryBlock* block = memlist;
	while(block != nullptr){
		std::cout << block->location << ' ' << block->reserved << ' ' << block->size << std::endl;
		block = block->next;
	}
	std::cout << std::endl;
}



class FirstFitAllocator : public Allocator{
	public:
		void* allocate(size_t size) override{
			MemoryBlock* block = memlist;
			while(block->size < size || block->reserved){
				block = block->next;
				if(block == nullptr)
					throw std::bad_alloc();
			}
			block->alloc(size);
			return block->location;
		}
		void deallocate(void* pointer) override{
			MemoryBlock* block = memlist;
			while(block->location != pointer){
				block = block->next;
			}
			block->dealloc();
		}
};

class BestFitAllocator : public Allocator{
	public:
		virtual void* allocate(size_t size){
			MemoryBlock* best = nullptr;
			MemoryBlock* block = memlist;
			while(block != nullptr){
				if(!block->reserved){
					if(block->size == size){
						best = block;
						break;
					}
					else if(block->size > size){
						if(best == nullptr)
							best = block;
						else if(block->size < best->size)
							best = block;
					}
				}
				block = block->next;
			}
			best->alloc(size);
			return best->location;
		}
		virtual void deallocate(void* pointer){
			MemoryBlock* block = memlist;
			while(block->location != pointer){
				block = block->next;
			}
			block->dealloc();	
		}
};

class CustomFitAllocator : public Allocator{
	public:
		virtual void* allocate(size_t size){	//allocates required memory from the start of the largest available block
			MemoryBlock* best = nullptr;
			MemoryBlock* block = memlist;
			while(block != nullptr){
				if(!block->reserved && block->size > size){
					if(best == nullptr)
						best = block;
					else if(block->size > best->size)
						best = block;
				}
				block = block->next;
			}
			best->alloc(size);
			return best->location;
		}
		virtual void deallocate(void* pointer){
			MemoryBlock* block = memlist;
			while(block->location != pointer){
				block = block->next;
			}
			block->dealloc();	
		}
};



class AllocatorSingleton{
	private:
		static Allocator* memory_manager;
	public:
		static int setFit(char fit){
			if(fit == 'b'){
				memory_manager = (Allocator*) malloc(sizeof(BestFitAllocator));
				new(memory_manager) BestFitAllocator;
				std::cout << "set best fit" << std::endl;
				return 1;
			}
			else if(fit == 'c'){
				memory_manager = (Allocator*) malloc(sizeof(CustomFitAllocator));
				new(memory_manager) CustomFitAllocator;
				std::cout << "set custom fit" << std::endl;
				return 2;
			}
			else if(fit == 'f'){
				memory_manager = (Allocator*) malloc(sizeof(FirstFitAllocator));
				new(memory_manager) FirstFitAllocator;
				std::cout << "set first fit" << std::endl;
				return 3;
			}
			else{
				memory_manager = (Allocator*) malloc(sizeof(Allocator));
				new(memory_manager) Allocator;
				std::cout << "set default c++ allocator" << std::endl;
				return 0;
			}
		}
		static Allocator* getAllocator(){
			return memory_manager;
		}
};

Allocator* AllocatorSingleton::memory_manager = nullptr;

void* operator new(size_t size){
	return AllocatorSingleton::getAllocator()->allocate(size);
}

void* operator new[](size_t size){
	return AllocatorSingleton::getAllocator()->allocate(size);
}

void operator delete(void* pointer){
	if(pointer == nullptr) return;
	return AllocatorSingleton::getAllocator()->deallocate(pointer);
}

void operator delete[](void* pointer){
	if(pointer == nullptr) return;
	return AllocatorSingleton::getAllocator()->deallocate(pointer);
}

void operator delete(void* pointer, size_t size){
	if(pointer == nullptr) return;
	return AllocatorSingleton::getAllocator()->deallocate(pointer);
}

void operator delete[](void* pointer, size_t size){
	if(pointer == nullptr) return;
	return AllocatorSingleton::getAllocator()->deallocate(pointer);
}

#endif