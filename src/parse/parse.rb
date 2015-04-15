require 'parser/current'
require 'thread'
require_relative './../builder'




# while data.children do 

# children.each do |child|
# 	puts child
# 	puts child.children
# 	child.children.each do |base|
# 		if base == nil
# 			puts "nil"
# 		else
# 			puts base
# 		end
# 		puts ""
# 	end
# end

# end


path = "assets/sp/"
filename = path + "nested_loop.txt"
#filename = path + "simple_sequence.txt"
#filename = path + "simple_chord.txt"
#filename = path + "simple_loop.txt"

file = File.open(filename, "rb")
contents = file.read

parser = Parser::CurrentRuby.new
parser.diagnostics.consumer = lambda do |diag|
  puts diag.render
end

buffer = Parser::Source::Buffer.new(filename)
buffer.source = contents
data = parser.parse(buffer)


puts "====Kids: "
children = data.children

# queue = Queue.new

# children.each do |child|
# 	queue << child
# 	while !queue.empty?() do
# 		curr = queue.pop()
# 		if curr.respond_to?(:children)
# 			curr.children.each do |child|
# 				queue << child
# 			end
# 		end
# 		puts curr
# 	end
# end

builder = Builder.new
stack = Array.new
parentIndex = 0;
nodeIndex = 0;

builder.makeRoot(data.type, nodeIndex)

data.children.each do |child|
	nodeIndex += 1
	stack.push([child, nodeIndex, parentIndex])
	while !stack.empty?() do
		curr = stack.pop()
		info = curr[0]
		puts info

		# puts "!!chunk!!"
		# puts nodeIndex
		# puts parentIndex
		# puts curr[1]
		# puts "!!chunk!!"
		if info.respond_to?(:type)
			builder.addNode(info.type, curr[1], curr[2])
		else
			puts info.to_s()
			if info.respond_to?(:children)
				puts "has children"
				puts info
			end
			builder.addValue(info.to_s(), curr[1], curr[2])
		end
		if info.respond_to?(:children)
			info.children.each do |child|
				nodeIndex += 1
				stack.push([child, nodeIndex, curr[1]])
			end
		end
	end
end

#create_child_nodes(builder, data.children, 0, 0) # root has index 0

# def create_child_nodes(builder, childArray, parentIndex, currIndex)
# 	childArray.each do |child|
# 		currIndex += 1
# 		if child == nil
# 			puts "nil"
# 		else
# 			#puts child
# 			if child.respond_to?(:type)
# 				builder.addNode(child.type, parentIndex)
# 			else
# 				puts child.to_s()
# 				if child.respond_to?(:children)
# 					puts "has children"
# 					puts child
# 				end
# 				builder.addValue(child.to_s(), parentIndex)
# 			end
# 			if child.respond_to?(:children)
# 				puts "====Kids::"
# 				parentIndex += 1
# 				create_child_nodes(builder, child.children, parentIndex)
# 			end
# 		end
# 	end
# end

#builder.entry(data.type)

file.close