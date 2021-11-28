from collections import deque
from dataclasses import dataclass

@dataclass
class LinearHashingStats:
  Count: int = 0
  Buckets: int = 1
  Pages: int = 0
  OverflowBuckets: int = 0
  Access: int = 0
  AccessInsertOnly: int = 0 #Done
  SplitCount: int = 0 #Done

class LinearHashing:

  def __init__(self, pagesize, policy = 0, maxoverflow = 0, sizelimit = 1.0):
    self.pagesize = pagesize
    self.policy = policy
    self.overflow = 0
    self.maxoverflow = maxoverflow
    self.sizelimit = sizelimit
    self.stats = LinearHashingStats()
    self.level = 0
    self.pointer = 0
    self.table = {0: deque()}

  def __split(self):
    self.stats.OverflowBuckets -= 1 if len(self.table[self.pointer]) > 1 else 0
    self.stats.Pages -= len(self.table[self.pointer])
    new = self.pointer + 2 ** self.level
    bucket_old = deque()
    bucket_new = deque()

    # Rehash values in bucket targeted for split
    for page in self.table[self.pointer]:
      self.stats.Access += 1
      for value in page:
        if value % (2 * 2 ** self.level) == self.pointer:
          if len(bucket_old) == 0 or len(bucket_old[-1]) == self.pagesize:
            bucket_old.append(list())
            self.stats.Pages += 1
          bucket_old[-1].append(value)
          self.stats.Access += 1
          self.stats.AccessInsertOnly += 1
        else:
          if len(bucket_new) == 0 or len(bucket_new[-1]) == self.pagesize:
            bucket_new.append(list())
            self.stats.Pages += 1
          bucket_new[-1].append(value)
          self.stats.Access += 1
          self.stats.AccessInsertOnly += 1

    # Place new buckets into hash table
    self.table[self.pointer] = bucket_old
    self.stats.OverflowBuckets += len(bucket_old) > 1
    self.table[new] = bucket_new
    self.stats.OverflowBuckets += len(bucket_new) > 1

    # Increment pointer and update level if necessary
    self.pointer = (self.pointer + 1) % (2 ** self.level)
    self.level += 0 if self.pointer else 1
    self.stats.SplitCount += 1
    self.stats.Buckets += 1

  def Insert(self, x):
    # Insert value
    key = x % (2 ** self.level)
    key = x % (2 * 2 ** self.level) if key < self.pointer else key
    if key not in self.table:
      self.table[key] = deque()
    if len(self.table[key]) == 0 or len(self.table[key][-1]) == self.pagesize:
      self.table[key].append(list())
      self.stats.Pages += 1
      if len(self.table[key]) == 2:
        self.stats.OverflowBuckets += 1
    self.table[key][-1].append(x)
    self.stats.Count += 1
    self.stats.Access += 1
    self.stats.AccessInsertOnly += 1

    # Determine if split is necessary based on policy
    split = (self.policy == 0 and len(self.table[key]) > 1
      or self.policy == 1 and self.stats.OverflowBuckets >= self.maxoverflow
      or self.policy == 2 and self.stats.Count / self.stats.Buckets / self.pagesize > self.sizelimit
      or self.policy == 3 and len(self.table[self.pointer]) > 1)
    
    # Perform split
    if split: self.__split()
    return split

  def Search(self, x):
    key = x % (2 ** self.level)
    key = x % (2 * 2 ** self.level) if key < self.pointer else key
    searched = 0
    for page in self.table[key]:
      searched += 1
      if x in page:
        self.stats.Access += searched
        return searched
    else:
      self.stats.Access += searched
      return searched * -1
  
  def Print(self, file = None):
    for key, bucket in self.table.items():
      line = f"{key:0{self.level}b} : "
      for page in bucket:
        line += str(page)[1:-1].replace(',', '')
        line += " - "
      print(line, file = file)
    print(f"Level: {self.level}", file = file)
    print(f"Ptr: {self.pointer:0{self.level}b}")
  
  def Count(self):
    return self.stats.Count

  def ListBucket(self, x):
    numbers = []
    for page in self.table[x]:
      numbers.extend(page)
    return numbers

  def GetStats(self):
    return self.stats

if __name__ == "__main__":
  from random import seed, randint
  LH0 = LinearHashing(500)
  LH1 = LinearHashing(500, policy = 1, maxoverflow = 0)
  LH2 = LinearHashing(500, policy = 2, sizelimit = 0.1)
  LH3 = LinearHashing(500, policy = 3)
  seed(1)
  for _ in range(10000):
    num = randint(0, 1000000)
    LH0.Insert(num)
    LH1.Insert(num)
    LH2.Insert(num)
    LH3.Insert(num)
  for _ in range(100000):
    num = randint(0, 1000000)
    LH0.Search(num)
    LH1.Search(num)
    LH2.Search(num)
    LH3.Search(num)
  print(LH0.stats)
  print(LH1.stats)
  print(LH2.stats)
  print(LH3.stats)