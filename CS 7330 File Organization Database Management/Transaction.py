class Transaction:

  def __init__(self, k):
    self.local = [None] * k

  def Read(self, db, source, dest):
