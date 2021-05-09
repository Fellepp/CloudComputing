#
#
# 
#
#
#----------------------------------------eje08firsttake.py---------------------------------------

from pyspark import SparkConf, SparkContext

sc = SparkContext("local[3]", "WordCount")

lines = sc.textFile("in/book.txt")
firstLine = lines.first()

print("First Line: %s" % firstLine)

threelines = lines.take(3)


for line in threelines:
	print("--> %s" % line)

