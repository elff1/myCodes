<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('classBasicInfo', 'Class Basic Infos')=>array('index'),
	InformationManagementModule::t('classBasicInfo', 'Manage ClassBasicInfo'),
);

//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('classBasicInfo', 'Create ClassBasicInfo'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('classBasicInfo', 'List ClassBasicInfo'), 'url'=>array('index')),
	//array('label'=>Yii::t('classBasicInfo','Manage ClassBasicInfo'), 'url'=>array('admin')),
	array('label'=>InformationManagementModule::t('classBasicInfo', 'Batch Create Class'), 'url'=>array('batchCreate')),
);

//高级搜索控件
Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('class-basic-info-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<?php echo "<h1>" . InformationManagementModule::t('classBasicInfo', 'Manage ClassBasicInfo') . "</h1>"; ?>

<?php echo CHtml::link(InformationManagementModule::t('other', 'Advanced Search'),'#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<!--显示数据表格的控件-->
<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'class-basic-info-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'name',
		'grade',
		'tutor_id',
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
