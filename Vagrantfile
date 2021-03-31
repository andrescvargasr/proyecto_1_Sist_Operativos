Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/xenial64"
  config.vm.provider "virtualbox" do |vb|
    vb.customize [ 'modifyvm', :id, '--name', 'proyecto1' ]
    vb.customize [ 'modifyvm', :id, '--cpus', '1' ]
    vb.customize [ 'modifyvm', :id, '--memory', '1024' ]
  end
end
