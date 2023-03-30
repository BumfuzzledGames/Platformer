#!/usr/bin/env ruby
require 'erb'
require 'json'

class String
    # Convert a string to a valid C identifier
    # This is mostly used to convert iid strings into C identifiers
    def c_ident
        gsub(/[^0-9a-z]/i, '_')
    end

    # Convert a hex color like "#010203" into "1, 2, 3"
    def hex_to_rgb
        match(/^#(..)(..)(..)$/).captures.map(&:hex)
    end

    def ldtk_type_to_c_type
        case self
        when "Int"
            "int"
        when "Float"
            "float"
        when "Bool"
            "SDL_bool"
        when "String"
            "const char *"
        when "Color"
            "SDL_Color"
        when "Tile"
            "LDtkFieldTileValue"
        when "EntityRef"
            "LDtkEntity *"
        when "Point"
            "SDL_Point"
        when /^Array<([^>]+)>$/
            $1.ldtk_type_to_c_type
        when /^LocalEnum\.(.+)$/
            "LDtkLocalEnum#{$1}"
        end
    end
end

## An LDtkField, which may be either on a level, or an entity
## f should be a field object
## p should be the c identifier of the parent object, such as entity_<iid>
#field = <<-ERB
#{
#    .identifier = "<%= f['__identifier'] %>",
#<%- if f['__type'] =~ /^Array</ -%>
#    // Arrays not yet supported
#<%- else -%>
#    .type = LDTK_FIELD_TYPE_<%= f['__type'] %>,
#    <%- if f['__type'] == 'Int' -%>
#    .int_value = <%= f['__value'] %>,
#    <%- elsif f['__type'] == 'Float' -%>
#    .float_value = <%= f['__value'] %>,
#    <%- elsif f['__type'] == 'Bool' -%>
#    .bool_value = <%= f['__value'] ? "SDL_TRUE" : "SDL_FALSE" %>,
#    <%- elsif f['__type'] == 'String' -%>
#    .string_value = "<%= f['__value'] %>",
#    <%- elsif f['__type'] == 'Color' -%>
#    .color_value = { <%= f['__value'].hex_to_rgb.join(', ') %>, 255 },
#    <%- elsif f['__type'] == 'EntityRef' -%>
#    .entityref_value = &ldtk_entity_<%= f['__value']['entityIid'].c_ident %>,
#    <%- elsif f['__type'] == 'Tile' -%>
#    .tile_value =
#    {
#        .tileset = &ldtk_tileset_<%= f['__value']['tilesetUid'] %>,
#        .src = { <%= f['__value']['x'] %>, <%= f['__value']['y'] %>, <%= f['__value']['w'] %>, <%= f['__value']['h'] %> },
#    },
#    <%- else -%>
#    <%- STDERR.puts "Unknown field type \#{f['__type']}" -%>
#    <%- end -%>
#<%- end -%>
#}
#ERB
#
generators = {
    'ldtk_world_enum.h' => 'src/ldtk_world_enum.h.erb',
    'ldtk_world_defs.h' => 'src/ldtk_world_defs.h.erb',
    'ldtk_world.c' => 'src/ldtk_world.c.erb'
}

j = JSON.parse(File.read(ARGV[0]))
generators.each do|k,v|
    if ARGV[1].end_with?(k)
        File.open(ARGV[1], "w+") do|f|
            f.write ERB.new(File.read(v), trim_mode:'-').result
        end
        exit 0
    end
end

puts "Invalid file requested '#{ARGV[1]}'"
exit -1