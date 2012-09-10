<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('program','Program')=>array('index'),
	InformationManagementModule::t('program','Manage Program'),
);

//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('program','List Program'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('program','Create Program'), 'url'=>array('create')),
);

//高级搜索控件
Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('program-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<h1><?php echo CHtml::encode(InformationManagementModule::t('program', 'Manage Program')); ?></h1>

<p class="note"><?php
	echo InformationManagementModule::t('other','You may optionally enter a comparison operator (<b>&lt;</b>, <b>&lt;=</b>, <b>&gt;</b>, <b>&gt;=</b>, <b>&lt;&gt;</b> or <b>=</b>) at the beginning of each of your search values to specify how the comparison should be done.'); /* no CHtml::encode here*/?></p>

<?php echo CHtml::link(InformationManagementModule::t('other','Advanced Search'),'#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<!--显示数据表格的控件-->
<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'program-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'name',
		array(
			'name'=>'department_id',
			'value'=>'$data->department===null?null:$data->department->name',
			'filter'=>Department::model()->departmentList,
		),
		array(
			'name'=>'length',
			'value'=>'$data->length===null?null:$data->lengthOptions[$data->length]',
			'filter'=>Program::model()->lengthOptions,
		),
		'grade',
		'introduction',
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
