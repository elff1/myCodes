<?php
$this->breadcrumbs=array(
	'Class Teachers'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List ClassTeacher', 'url'=>array('index')),
	array('label'=>'Manage ClassTeacher', 'url'=>array('admin')),
);
?>

<h1>Create ClassTeacher</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>