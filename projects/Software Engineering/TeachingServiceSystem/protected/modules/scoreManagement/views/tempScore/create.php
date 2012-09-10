<?php
$this->breadcrumbs=array(
	'Temp Scores'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List TempScore', 'url'=>array('index')),
	array('label'=>'Manage TempScore', 'url'=>array('admin')),
);
?>

<h1>Create TempScore</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>