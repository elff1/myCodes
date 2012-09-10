<?php
$this->breadcrumbs=array(
	'Teachingclass Infos'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List TeachingclassInfo', 'url'=>array('index')),
	array('label'=>'Manage TeachingclassInfo', 'url'=>array('admin')),
);
?>

<h1>Create TeachingclassInfo</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>