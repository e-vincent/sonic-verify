require 'parser/current'
require_relative '../../bin/verify'

path = "src/assets/sp/"

filename = path + "conditional_in_loop.txt"
#filename = path + "sequence_loop.txt"
#filename = path + "simple_loop.txt"
#filename = path + "prog_function.txt"

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
blkStack = Array.new
parentIndex = 0
nodeIndex   = 0
statementNo = 0
beginPos 	= 0
intFlag		= false
symFlag		= false
ifFlag		= false
line		= 0

builder.makeRoot(data.type)

data.children.each do |child|
	stack.push([child, nodeIndex, parentIndex])
	while !stack.empty?() do
		nodeIndex += 1
		curr = stack.pop()
		info = curr[0]
		curr[1] = nodeIndex

puts info
		if info.respond_to?(:location) and info.location.expression != nil	
			if info.location.expression.line > line
				line = info.location.expression.line
			end

			if ("send".eql?(info.type.to_s())) || ("if".eql?(info.type.to_s()))
				statementNo += 1
			end	
			
			# if the current node has the same parent as the top block
			# pop it because we are outside of the last block tree
			# puts "Current stack size: #{blkStack.size()}"
			# puts "Looking at blkStack top: #{blkStack[blkStack.size() - 1]}"
			# puts "Given parent: #{curr[2]}"
			if curr[2] == blkStack[blkStack.size() - 1]
				blkStack.pop()
				builder.exitFuncs(statementNo)
			end
			# handling detection of block level
			# used later to track where in the trace index internal function VT is stored
			if "block".eql?(info.type.to_s())
				blkStack.push(curr[2])
			end
		end

		if info.respond_to?(:type)
			intFlag = "int".eql?(info.type.to_s()) || "float".eql?(info.type.to_s())
			symFlag = "sym".eql?(info.type.to_s())
			ifFlag  = "if".eql?(info.type.to_s())
			if intFlag
				int = info.children[0]
				builder.addNumber(int.to_s(), curr[1], curr[2], line, statementNo, blkStack.size())
			elsif symFlag
				sym = info.children[0]
				builder.addSymbol(sym.to_s(), curr[1], curr[2], line, statementNo, blkStack.size())
			elsif ifFlag
				cond = info.children[0] # throwing it for the moment => will want a mini tree later?
				builder.addIf(curr[1], curr[2], line, statementNo, blkStack.size())
			else
				builder.addNode(info.type, curr[1], curr[2], line, statementNo, blkStack.size())
			end
		else
			builder.addValue(info.to_s(), curr[1], curr[2], line, statementNo, blkStack.size())
		end

		if info.respond_to?(:children)
			if !intFlag && !symFlag
				info.children.reverse.each_with_index do |child, index|
					if ifFlag && (index == info.children.size - 1)
						ifFlag = false
						# want to avoid first child but add the rest
						# since we're reverse iterating, this means avoid last loop
					else
						stack.push([child, -1, curr[1]])
					end
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