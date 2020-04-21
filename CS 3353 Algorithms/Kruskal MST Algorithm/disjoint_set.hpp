#ifndef DISJOINT_SET
#define DISJOINT_SET

#include <vector>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <exception>

template <typename element>
class DisjointSet{
	public:
		virtual uint makeSet(element) = 0;
		virtual uint findSet(element) = 0;
		virtual void setUnion(element, element) = 0;
		virtual void clear() = 0;
};



template <typename element>
class DisjointSetTrivial : public DisjointSet<element>{
	private:
		typedef std::list<element> subset;
		std::vector<subset> subsets;

	public:
		uint makeSet(element target){
			subsets.emplace_back(subset(1, target));
			return subsets.size() - 1;
		}
		uint findSet(element target){
			uint index = 0;
			for (const subset& subset : subsets){
				if (std::find(subset.begin(), subset.end(), target) != subset.end()){
					return index;
				}
				++index;
			}
			throw std::domain_error("Element does not exist in disjoint set");
		}
		void setUnion(element target1, element target2){
			subset& subset1 = subsets[findSet(target1)];
			subset& subset2 = subsets[findSet(target2)];
			if (&subset1 == &subset2){
				throw std::domain_error("Cannot compute the union of a set and itself");
			}
			subset1.splice(subset1.end(), subset2);
		}
		void clear(){
			subsets.clear();
		}
};



template <typename element>
class DisjointSetOptimized : public DisjointSet<element>{
	private:
		typedef std::list<element> subset;
		std::unordered_map<uint, subset> subsets;
		std::unordered_map<element, uint> subsetIDs;

	public:
		uint makeSet(element target){
			subsets.emplace(subsetIDs.size(), subset(1, target));
			subsetIDs.emplace(target, subsetIDs.size());
			return subsetIDs.size() - 1;
		}
		uint findSet(element target){
			return subsetIDs[target];
		}
		void setUnion(element target1, element target2){
			const uint& subset1ID = subsetIDs[target1];
			subset& subset1 = subsets[subsetIDs[target1]];
			subset& subset2 = subsets[subsetIDs[target2]];
			if (&subset1 == &subset2){
				throw std::domain_error("Cannot compute the union of a set and itself");
			}
			for (const element& target : subset2){
				subsetIDs[target] = subset1ID;
			}
			subset1.splice(subset1.begin(), subset2);
		}
		void clear(){
			subsets.clear();
		}
};

#endif