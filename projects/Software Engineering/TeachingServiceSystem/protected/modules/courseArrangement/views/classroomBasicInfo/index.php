<?php
$this->breadcrumbs=array(
	'教室信息',
);

$this->menu=array(
	array('label'=>yii::t('courseArrangement', 'View Classroom'), 'url'=>array('index')),
	array('label'=>yii::t('courseArrangement', 'Create Classroom'), 'url'=>array('create')),
	array('label'=>yii::t('courseArrangement', 'Manage Classroom'), 'url'=>array('admin')),
	
);
?>

<h1>教室信息</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
