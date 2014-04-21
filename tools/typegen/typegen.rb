#!/usr/bin/env ruby

#
# The "ty" files are in lazily parsable "one thing on a line" format.
#
# %type type_name
#
#   Must match file name.
#
#
# A type must have either "%prim" or "%data"
#
# %prim c_type
# 
#   This is a primitive. No need to alloc, pass a pointer, do
#   initialization, or cleanup.
#
#
# %data
#
#   A static list. All types have a constant, static size.
#   
#   Variable size types have one or more pointer members.
#
#
# %meth method_name(arg list) -> return_type
#
#   Defines a method. Implicit self for all methods, including alloc.
#
#
# Required methods:
#
#   uint64_t hash()
#
#  
# Required for non-primitives:
#
#   T* alloc(types, ...)
# 
#
# Methods are named s#{type}_name

require 'pathname'

source = Pathname.new(ARGV[0])

type_name = /^(\w+)\.ty$/.match(source.basename.to_s)[1]

mode = nil
prim = nil
data = nil
type = nil

methods = {}
sections = {}

source.each_line do |line|
  case line
  when /^#/
    headers << line
  when /^%type (\w+)/
    if $1 != type_name
      raise Exception.new("Type name mismatch: #{$1} ne #{type_name}")
    end
    type = $1
  when /^%prim (\w+)/
    prim = $1
  when /^%data/
    mode = "__data"
  when /^%meth (\w+)\((.*?)\)\s*->\s*(\w+)\s*$/
    mode = "meth:#{$1}"
    methods[$1] = { args: $2, retv: $3 }
  when /^%meth (\w+)\((.*?)\)\s*$/
    mode = "meth:#{$1}"
    methods[$1] = { args: $2, retv: 'void' }
  when /^{/
    # skip
  when /^}/ 
    # skip
  else
    sections[mode] ||= []
    sections[mode] << line
  end
end

raise Exception.new("Must specify %type name") if type.nil?
raise Exception.new("Must specify %prim or %data") if data.nil? && prim.nil?
raise Exception.new("Can't have both %prim and %data") unless data.nil? || prim.nil?

puts sections.inspect
puts methods.inspect
