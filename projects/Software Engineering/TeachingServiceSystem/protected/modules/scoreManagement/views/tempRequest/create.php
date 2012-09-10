<?php
$this->breadcrumbs=array(
	'Temp Requests'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List TempRequest', 'url'=>array('index')),
	array('label'=>'Manage TempRequest', 'url'=>array('admin')),
);
?>

<h1>Create TempRequest</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>