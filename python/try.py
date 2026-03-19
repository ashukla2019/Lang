class MyClass(object):
    limit = 10

    def __init__(self):
        self.data = []

    def item(self, i):
        return self.data[i]

    def add(self, e):
        if len(self.data) >= self.limit:
            raise Exception("Too many elements")
        self.data.append(e)

myclass = MyClass()
myclass.add("Amit")
myclass.add("Ankit")
print myclass.data
