require 'parser/current'
require_relative '../../bin/verify'

path = "src/assets/sp/"

#filename = path + "function_simple.txt"
#filename = path + "sequence_loop.txt"
#filename = path + "simple_chord.txt"
filename = path + "prog_function.txt"

file = File.open(filename, "rb")
contents = file.read

parser = Parser::CurrentRuby.new
parser.diagnostics.consumer = lambda do |diag|
  puts diag.render
end

# parse will throw an error on syntax error
# will need a useful syntax guard
buffer = Parser::Source::Buffer.new(filename)
buffer.source = contents
data = parser.parse(buffer)

children = data.children

# pass builder through to avoid static use of tree
builder  = Builder.new
stack    = Array.new
parentIndex = 0
nodeIndex   = 0
statementNo = 0
beginPos 	= 0
intFlag		= false
symFlag		= false
line		= 0

builder.makeRoot(data.type)

data.children.each do |child|
	stack.push([child, nodeIndex, parentIndex])
	while !stack.empty?() do
		nodeIndex += 1
		curr = stack.pop()
		info = curr[0]
		curr[1] = nodeIndex

		if info.respond_to?(:location) and info.location.expression != nil	
			if info.location.expression.line > line
				line = info.location.expression.line
			end

			if "send".eql?(info.type.to_s())
				statementNo += 1
			end		
		end

		if info.respond_to?(:type)
			intFlag = "int".eql?(info.type.to_s()) || "float".eql?(info.type.to_s())
			symFlag = "sym".eql?(info.type.to_s())
			if intFlag
				int = info.children[0]
				builder.addNumber(int.to_s(), curr[1], curr[2], line, statementNo)
			elsif symFlag
				sym = info.children[0]
				builder.addSymbol(sym.to_s(), curr[1], curr[2], line, statementNo)
			else
				intFlag = false
				symFlag = false
				builder.addNode(info.type, curr[1], curr[2], line, statementNo)
			end
		else
			intFlag = false
			symFlag = false
			builder.addValue(info.to_s(), curr[1], curr[2], line, statementNo)
		end

		if info.respond_to?(:children)
			if !intFlag && !symFlag
				info.children.reverse.each do |child|
					stack.push([child, -1, curr[1]])
				end
			end
		end

		# puts "=== STACK ==="
		# stack.each_with_index do |item, index|
		# 	puts "stack_mem: #{index}"
		# 	puts "#{item[0]}"
		# end
		# puts ""
	end
end

puts "Statements #{statementNo}"
puts "Lines #{line}"

builder.setTreeSize(statementNo, line)

# this must come after builder has created the tree
# otherwise it has no information to process and will die
analyser = TimeMarker.new

file.close