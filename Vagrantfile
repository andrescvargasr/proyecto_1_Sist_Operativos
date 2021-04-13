Vagrant.configure("2") do |config|
      config.vm.box = "ubuntu/xenial64"
	  config.vm.provider "virtualbox" do |vb|
	  config.vm.provision "shell", path: "aprovisionamiento.sh"
	    vb.customize [ 'modifyvm', :id, '--name', 'proyecto' ]
		vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
        vb.customize [ 'modifyvm', :id, '--memory', '1024' ]
      end
end
