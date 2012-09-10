<?php
$this->breadcrumbs=array(
	'Teachingclass Infos'=>array('index'),
	$model->class_id=>array('view','id'=>$model->class_id),
	'Update',
);

$this->menu=array(
	array('label'=>'List TeachingclassInfo', 'url'=>array('index')),
	array('label'=>'Create TeachingclassInfo', 'url'=>array('create')),
	array('label'=>'View TeachingclassInfo', 'url'=>array('view', 'id'=>$model->class_id)),
	array('label'=>'Manage TeachingclassInfo', 'url'=>array('admin')),
);
?>

<h1>Update TeachingclassInfo <?php echo $model->class_id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>