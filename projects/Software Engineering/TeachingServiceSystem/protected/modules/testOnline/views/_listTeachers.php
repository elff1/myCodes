
<h1>Teacher List</h1>
<?php
$this->breadcrumbs=array(
	'OnlineTest Subsystem',
);
?>
<?php 
$this->widget('zii.widgets.grid.CGridView', array(
			'id'=>'list-teachers-grid',
			'dataProvider'=>AccountComponent::getTeacherList(),
			'filter'=>TeacherBasicInfo::model(),
			'columns'=>array(
					'teacher_id',
					'title',
					'department_id',
					array('class'=>'CButtonColumn', 'template'=>'{view}',
					'buttons'=>array(
						'view' => array(
								'url'=>'Yii::app()->createUrl("testOnline/default/updateSelectedTeacher",array("teacher_id"=>$data->id))',
						),
					)
			),
			),
	));
?>