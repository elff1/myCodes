<?php
$this->breadcrumbs=array(
	'Classroom Basic Infos'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'View Classroom'), 'url'=>array('index')),
	array('label'=>yii::t('courseArrangement', 'Create Classroom'), 'url'=>array('create')),
	array('label'=>yii::t('courseArrangement', 'Manage Classroom'), 'url'=>array('admin')),
	//array('label'=>'ClassroomBasicInfo', 'url'=>array('view', 'id'=>$model->id)),
);
?>

<h1>Update ClassroomBasicInfo <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>