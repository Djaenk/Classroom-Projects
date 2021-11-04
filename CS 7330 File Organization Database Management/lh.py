class LinearHashing:

  def __init__(self, pagesize, policy = 0, maxoverflow = 0, sizelimit = 1.0):
    self.pagesize = pagesize
    self.policy = policy
    self.overflow = 0
    self.maxoverflow = maxoverflow
    self.sizelimit = sizelimit
    self.level = 0
    self.pointer = 0
    self.table = {0: deque(list())}

  def split(self):
    new = self.pointer + 2 ** self.level
    bucket_old = deque(list())
    bucket_new = deque(list())
    # Iterate through values in bucket targeted for split
    for value in table[bucket_old]:
      # Rehash values and send to split buckets
      if value % (2 ** self.level) == new:
        bucket_old[-1].append(value)
      else:
        bucket_new[-1].append(value)
      # If last page in new bucket(s) is full, add new page
      if len(bucket_old[-1]) == self.pagesize:
        bucket_old.append(list())
      if len(bucket_new[-1]) == self.pagesize:
        bucket_new.append(list())
    # Place new buckets into hash table
    table[self.pointer] = bucket_old
    table[new] = bucket_new
    # Increment pointer and update level if necessary
    self.pointer += 1
    if self.pointer == 2 ** self.level:
      self.pointer = 0
      self.level += 1