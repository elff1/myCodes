<?php
$this->breadcrumbs=array(
	Yii::t('base','Departments')=>array('index'),
	$model->name,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>Yii::t('department','List Department'), 'url'=>array('index')),
	array('label'=>Yii::t('department','Create Department'), 'url'=>array('create')),
	array('label'=>Yii::t('department','Update Department'), 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>Yii::t('department','Delete Department'), 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>Yii::t('base','Are you sure you want to delete this item?'))),
	array('label'=>Yii::t('department','Manage Department'), 'url'=>array('admin')),
);
?>

<h1>View Department #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'name',
	),
)); ?>
