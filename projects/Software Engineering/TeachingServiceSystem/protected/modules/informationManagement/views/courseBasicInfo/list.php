<?php
$this->breadcrumbs=array(
	InformationManagementModule::t('course','Course')=>array('list'),
	InformationManagementModule::t('course','Course List'),
);

/* $this->menu=array(
	array('label'=>'List CourseBasicInfo', 'url'=>array('index')),
	array('label'=>'Create CourseBasicInfo', 'url'=>array('create')),
); */

Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('course-basic-info-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<?php echo "<h1>" . InformationManagementModule::t('course','Course List') . "</h1>"; ?>

<?php echo CHtml::link(InformationManagementModule::t('other','Advanced Search'),'#', array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'course-basic-info-grid',
	'dataProvider'=>$model->search(),
	//'filter'=>$model,
	//'hideHeader'=>true,
	'columns'=>array(
		array(
            'header' => InformationManagementModule::t('course','Course Code'),
            'value' => '$data->course_id',
        ),
		array(
            'header' => InformationManagementModule::t('course','Course Name'),
            'value' => '$data->name',
        ),
		array(
            'header' => InformationManagementModule::t('course','Course Credit'),
            'value' => '$data->credit',
        ),
		array(
            'header' => InformationManagementModule::t('course','Course Class'),
            'value' => '$data->class',
        ),
		/* 'id',
		'course_id',
		'name',
		'credit',
		'class',
		'prerequsite_required', */
		/*
		'introduction',
		'syllabus',
		'department_id',
		'priority',
		*/
		/* array(
			'class'=>'CButtonColumn',
		), */
	),
)); ?>
