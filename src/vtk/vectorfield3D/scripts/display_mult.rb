#!/usr/bin/ruby

require 'orocos'
require 'vizkit'

include Orocos

Orocos.initialize

gui = Vizkit.default_loader.Vectorfield3D

gui.resize(1024,768)
gui.setBackground(0,0,0)
#gui.setInitialMagRange(0.0,7e-05)
gui.addVector(0,0,0,0,0,0)
gui.addVector(1,0,0,0,0,0)
gui.addVector(2,0,0,0,0,0)
gui.addVector(3,0,0,0,0,0)
gui.addVector(4,0,0,0,0,0)
gui.setCameraPosition(-0.5,-0.5,0.5)
gui.setCameraViewUp(0,0,1)

mag = Orocos::Async.proxy("mag")

mag.port("calibrated_values").on_data do |data|
    sensor0 = data[0]
    sensor1 = data[1]
    sensor2 = data[2]
    sensor3 = data[3]
    sensor4 = data[4]

    gui.adaptVector(0,0,0,0,sensor0.mag[0],sensor0.mag[1],sensor0.mag[2])
    gui.adaptVector(1,1,0,0,sensor1.mag[0],sensor1.mag[1],sensor1.mag[2])
    gui.adaptVector(2,2,0,0,sensor2.mag[0],sensor2.mag[1],sensor2.mag[2])
    gui.adaptVector(3,3,0,0,sensor3.mag[0],sensor3.mag[1],sensor3.mag[2])
    gui.adaptVector(4,4,0,0,sensor4.mag[0],sensor4.mag[1],sensor4.mag[2])
    data
end

gui.show
Vizkit.exec
