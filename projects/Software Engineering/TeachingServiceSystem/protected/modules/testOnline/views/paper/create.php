<?php
$this->breadcrumbs=array(
	'Online Test Subsystem'=>array('/testOnline'),
	'Paper Bank'=>array('paperBank/'),
//	'Papers'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List Paper', 'url'=>array('index')),
	array('label'=>'Manage Paper', 'url'=>array('admin')),
);
?>

<h1>Create Paper</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>