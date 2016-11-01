# -*- mode: ruby -*-
# vi: set ft=ruby :

# The MIT License (MIT)
# 
# Copyright (c) 2016 Kevin Brightwell
#
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# This vagrantfile is used for creating a ubuntu trusty environment for 
# building the procsim project

require 'dotenv'

Dotenv.load

Vagrant.configure("2") do |config|
  cpu_count   = ENV.has_key?("CPUS") ? ENV["CPUS"] : 1
  memory_size = ENV.has_key?("MEMORY") ? ENV["MEMORY"] : 1024
  vram_size   = ENV.has_key?("VRAM") ? ENV["VRAM"] : 128 

  with_gui    = ENV.has_key?("WITH_GUI") ? (ENV["WITH_GUI"]) : true
  with_gui    = (with_gui || with_gui == "true" || with_gui == "1")

  host_port = ENV.has_key?("HOST_PORT") ? ENV["HOST_PORT"] : 9000
  guest_port = ENV.has_key?("GUEST_PORT") ? ENV["GUEST_PORT"] : 9000

  puts ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
  puts "Hardware Configuration:"
  puts "\tCPUS\t\t= #{cpu_count}"
  puts "\tRAM\t\t= #{memory_size}"
  puts "\tVRAM\t\t= #{vram_size}"
  puts "\tGUI\t\t= #{with_gui}"
  puts "\tPORT FWD\t= #{host_port} -> #{guest_port}"
  puts ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"

  config.vm.box = "bento/ubuntu-16.04"

  config.vm.network "forwarded_port", guest: host_port, host: guest_port
  
  config.vm.provider "virtualbox" do |vb|
    vb.cpus = cpu_count
    vb.memory = memory_size
    
    vb.gui = with_gui
    if with_gui
      vb.customize ["modifyvm", :id, "--vram", "#{vram_size}"]
    end
  end

  # Install/update prerequisite software:

  config.vm.provision "shell", privileged: false, 
    inline: "sed -i '1i force_color_prompt=yes' ~/.bashrc"

  config.vm.provision "shell", privileged: true, inline: <<-EOF
    apt-add-repository ppa:george-edison55/cmake-3.x -y

    apt-get update -qq
  EOF

  config.vm.provision "shell", privileged: true, inline: <<-EOF
    echo "Installing build prequisisites: git, cmake"
    apt-get install -q -y git cmake
  EOF

  config.vm.provision "shell", privileged: true, inline: <<-EOF
    echo "Installing build compiler toolchains: gcc-5"

    apt-get install -q -y gcc g++ gdb
  EOF

  config.vm.provision "shell", privileged: true, inline: <<-EOF
    echo "Installing build dependencies: boost, ninja"
    
    apt-get install -qq -y libboost1.58-all-dev ninja-build
  EOF
  
  config.vm.provision "shell", privileged: true, inline: <<-EOM
    echo "Creating alternatives for clang and gcc"

    update-alternatives --install /usr/bin/cc cc `which gcc-5` 30
    update-alternatives --install /usr/bin/c++ c++ `which g++-5` 30
  EOM
  
  if ENV.has_key?("WORKSPACE")
    WORKSPACE = ENV["WORKSPACE"]
    config.vm.provision "shell", run: "always", inline: "echo 'Linking workspace: ~/workspace -> #{WORKSPACE}'"
    
    config.vm.synced_folder WORKSPACE, "/home/vagrant/workspace"
  end

  if with_gui
    config.vm.provision "shell", privileged: true, inline: <<-EOF
      apt-get install -y -q kdevelop konsole
      apt-get install -y -q ubuntu-desktop --no-install-recommends
      apt-get install -y -q unity evince unity-lens-files unity-lens-applications 
    EOF
  end

  # Do this last since it's best to make sure everyone else is updated first
  config.vm.provision "shell", privileged: true, inline: <<-EOF
    apt-get autoremove --purge -y
    apt-get dist-upgrade -y -q 
    apt-get autoremove --purge -y
  EOF
  
  config.vm.provision :reload
end # end vagrant file 
