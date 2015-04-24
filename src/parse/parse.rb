require 'parser/current'
require_relative '../../bin/verify'

path = "src/assets/sp/"

#filename = path + "nested_loop.txt"
#filename = path + "simple_sequence.txt"
filename = path + "simple_chord.txt"
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

children = data.children

# pass builder through to avoid static use of tree
builder  = Builder.new
stack    = Array.new
parentIndex = 0
nodeIndex   = 0

builder.makeRoot(data.type)

data.children.each do |child|
	nodeIndex += 1
	stack.push([child, nodeIndex, parentIndex])
	while !stack.empty?() do
		curr = stack.pop()
		info = curr[0]

		if info.respond_to?(:type)
			builder.addNode(info.type, curr[1], curr[2])
		else
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

# this must come after builder has created the tree
# otherwise it has no information to process and will die
analyser = TimeMarker.new

file.close