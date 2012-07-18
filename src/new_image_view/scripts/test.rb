#!/usr/bin/env ruby

require 'orocos/log'
#require 'testgui.rb'
require 'vizkit'
include Orocos

@line_ctr = 0;
@line_direction = 1;

@frame_width = 600
@frame_height = 300

def rotate
    @view.rotate(90)
end

def add_line
    
    
    @view.addLine(Qt::LineF.new(@line_ctr, 0, @line_ctr, @frame_height), false);
    if(@line_ctr == @frame_height)
        @line_direction = -1
    elsif(@line_ctr == 0)
        @line_direction = 1
    end
    @line_ctr = @line_ctr + @line_direction
end

def add_circle
    max_radius = 100
    @view.addCircle(Qt::PointF.new(rand(@frame_width), rand(@frame_height)), rand(max_radius), true)
end

def clear_overlays
    @view.clearOverlays(true);
end



if ARGV.length != 1
    puts "Please supply a logfile as argument."
    exit
end



log = Log::Replay.open(ARGV[0])

@view = Vizkit.default_loader.NewImageView
@view.extend QtTypelibExtension
@view.show

@view.addCircle(Qt::PointF.new(0,0), 50, true);

#@view.addLine(Qt::LineF.new(200, 0, 200, 300))
#@view.addLine(Qt::LineF.new(250, 0, 250, 300))

@testgui = Vizkit.load(File.join(File.dirname(__FILE__),'testgui.ui'))
@testgui.show

@testgui.rotate_button.connect(SIGNAL('clicked()')) {rotate}
@testgui.line_button.connect(SIGNAL('clicked()')) {add_line}
@testgui.circle_button.connect(SIGNAL('clicked()')) {add_circle}
@testgui.clear_overlays_button.connect(SIGNAL('clicked()')) {clear_overlays}


log.front_camera.frame.connect_to @view

Vizkit.control log

Vizkit.exec